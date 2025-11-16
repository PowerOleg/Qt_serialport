#include <QDebug>
#include <QtSerialPort>
#include "uart_controller.h"

UartController::UartController(QObject *parent) : QObject{parent}
{
    port = new QSerialPort();
    connect(port, &QSerialPort::readyRead, this, &UartController::SlotRead);
    connect(port, &QSerialPort::bytesWritten, [](qint64 bytes)
    {
        qDebug() << "Отправлено байт:" << bytes;
    });
    connect(port, &QSerialPort::errorOccurred, [this](QSerialPort::SerialPortError error)
    {
        if (error == QSerialPort::ResourceError)
        {
            qDebug() << "Ошибка порта:" << port->errorString();
            port->close();
        }
    });
}

UartController::~UartController()
{
    delete port;
}

void UartController::SlotRead()
{
    QByteArray received = port->read(receiveMessageSize);
    if (received.size() == 2)
    {
        int x = static_cast<int>(static_cast<unsigned char>(received[0]));
        int y = static_cast<int>(static_cast<unsigned char>(received[1]));
        emit SendDataToScreen(x, y);
    }
    received.clear();
}

void UartController::SlotEnable()
{
    QByteArray byteArray;//=QByteArray::fromHex("01");
    byteArray.resize(0);
    byteArray.append(static_cast<char>(0x01));
    receiveMessageSize = 2;
    SendData(byteArray, byteArray.size());
}

void UartController::SendData(QByteArray &byteArray, int length)
{
    if (!port->isOpen())
    {
        qDebug() << "Порт не открыт!";
        return;
    }
    if (byteArray.length() == length)
    {
        for (int i = 0; i<length; i++)
        {
            QByteArray temp;
            temp.resize(0);
            temp.append(byteArray[i]);
            port->write(temp);
            port->flush();
            //port->waitForBytesWritten();//waitForBytesWritten блокирует поток и readyRead всё крашит
            temp.clear();
        }
        byteArray.clear();
    }
}

void UartController::SlotDisableLed()
{
    QByteArray byteArray;
    byteArray.resize(0);
    byteArray.append(static_cast<unsigned char>(0x02));
    receiveMessageSize = 1;
    SendData(byteArray, byteArray.size());
}

void UartController::SlotInit()
{
    if (PortInit("COM3"))//"/dev/ttyUSB0" в Linux
    {
        qDebug() << "Port Opened!";
    }
    else
    {
        qDebug() << "Port Failure!";
    }
}

void UartController::SlotClosePort()
{
    port->close();
}

bool UartController::PortInit(QString name)
{
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setPortName(name);//"/dev/ttyUSB0" в Linux //"/dev/ttyACM0"
    port->close();//Закрываем порт
    return port->open(QSerialPort::ReadWrite);
}

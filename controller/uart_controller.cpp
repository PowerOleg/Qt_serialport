#include "uart_controller.h"

UartController::UartController(QObject *parent) : QObject{parent}
{
    port = new QSerialPort();
//    buffer = new Data();
    connect(port, &QSerialPort::readyRead, this, &UartController::slotRead);
    connect(port, &QSerialPort::bytesWritten, [](qint64 bytes) {//port->waitForBytesWritten();//waitForBytesWritten блокирует поток и readyRead всё крашит
        qDebug() << "Отправлено байт:" << bytes;
    });
    connect(port, &QSerialPort::errorOccurred, [this](QSerialPort::SerialPortError error) {
        if (error == QSerialPort::ResourceError) {
            qDebug() << "Критическая ошибка порта!" << port->errorString();
            port->close();
        }
    });
}

UartController::~UartController()
{
    delete port;
//    delete buffer;
}

void UartController::slotRead()
{
    QByteArray received = port->read(receivedMessageSize);
    qDebug() << "Получены данные (hex):" << received.toHex();


//    for (char byte : received)
//    {
//        qDebug() << static_cast<int>(static_cast<unsigned char>(byte));
//    }





//    buffer->Clear();
//    buffer->SetData(received);
//    emit sendDataToScreen(byteArray);//отправить данные в график
}

void UartController::slotEnableLed()
{
    QByteArray byteArray;//=QByteArray::fromHex("01");
    byteArray.resize(0);
    byteArray.append(static_cast<char>(0x01));
    receivedMessageSize = 2;
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
            temp.clear();
        }
        byteArray.clear();
    }
}

void UartController::slotDisableLed()
{
    QByteArray byteArray;
    byteArray.resize(0);
    byteArray.append(static_cast<unsigned char>(0x02));
    receivedMessageSize = 1;
    SendData(byteArray, byteArray.size());
}

void UartController::slotInit()
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

void UartController::slotClosePort()
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

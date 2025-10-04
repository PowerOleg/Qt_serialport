#include "uart.h"

UART::UART(QObject *parent)
    : QObject{parent}
{
    Port = new QSerialPort(this);
    connect(Port,&QSerialPort::readyRead,this,&UART::slotRead);
}

bool UART::PortInit(QString name)
{
    Port->setParity(QSerialPort::NoParity);
    Port->setStopBits(QSerialPort::OneStop);
    Port->setDataBits(QSerialPort::Data8);
    Port->setFlowControl(QSerialPort::NoFlowControl);
    Port->setBaudRate(QSerialPort::Baud9600);
    Port->setPortName(name);
    Port->close();//Закрываем порт
    if(Port->open(QSerialPort::ReadWrite))
    {
        return true;
    }
    else
        return false;
}

void UART::sendData(QByteArray data, int length)
{
    if(data.length() == length)
    {
        for(int i = 0;i<length;i++)
        {
            QByteArray temp;
            temp.resize(1);
            temp.append(data[i]);
            Port->write(temp);
            Port->waitForBytesWritten();
            temp.clear();
        }
        data.clear();
    }
}

void UART::slotRead()
{
    QByteArray arr;
    arr.append(Port->readAll());
    if(arr.length()>=Rxlength)
    {
        RxArr.clear();
        RxArr = arr;
        arr.clear();
    }
}

void UART::slotEnableLed()
{
    TxArr.clear();
    TxArr.resize(1);
    TxArr.append(static_cast<char>(1));
    sendData(TxArr,1);
}
void UART::slotDisableLed()
{
    TxArr.clear();
    TxArr.resize(1);
    TxArr.append(static_cast<char>(0));
    sendData(TxArr,1);
}

void UART::setRxLength(int length)
{
    Rxlength = length;
}

void UART::slotInit()
{
    PortInit("COM3");
}

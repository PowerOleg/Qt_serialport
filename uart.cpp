#include "uart.h"

UART::UART(QObject *parent)
    : QObject{parent}
{
    Port = new QSerialPort(this);
    connect(Port,&QSerialPort::readyRead,this,&UART::slotRead);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

bool UART::PortInit(QString name)
{
    Port->setParity(QSerialPort::NoParity);
    Port->setStopBits(QSerialPort::OneStop);
    Port->setDataBits(QSerialPort::Data8);
    Port->setFlowControl(QSerialPort::NoFlowControl);
    Port->setBaudRate(QSerialPort::Baud9600);
    Port->setPortName(name);
    Port->close();//Закрываем порт от греха по дальше =)
    if(Port->open(QSerialPort::ReadWrite))
    {
        return true;
    }
    else
        return false;
}

void UART::sendData(QByteArray Data, int length)
{
if(Data.length() == length)
{
for(int i = 0;i<length;i++)
{
QByteArray temp;
temp.resize(1);
temp.append(Data[i]);
Port->write(temp);
Port->waitForBytesWritten();
temp.clear();
}
Data.clear();
}
}

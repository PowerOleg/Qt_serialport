#include "uart.h"

UART::UART(QObject *parent)
    : QObject{parent}
{
    Port = new QSerialPort(this);
    connect(Port,&QSerialPort::readyRead,this,&UART::slotRead);
}

void UART::slotRead()
{
    QByteArray arr;
    arr.append(Port->readAll());
    qDebug()<< "Data IN: "<< arr;
    arr.clear();
}

void UART::slotEnableLed()
{
    TxArr.clear();
    TxArr.resize(0);
    TxArr.append(static_cast<char>(1));
    sendData(TxArr,1);
}

void UART::sendData(QByteArray Data, int length)
{
    qDebug()<<Data;
    if(Data.length() == length)
    {
        for(int i = 0;i<length;i++)
        {
            QByteArray temp;
            temp.resize(0);
            temp.append(Data[i]);
            Port->write(temp);
            Port->waitForBytesWritten();
            temp.clear();
        }
        Data.clear();
    }
}

void UART::slotDisableLed()
{
    TxArr.clear();
    TxArr.resize(0);
    TxArr.append(static_cast<char>(2));
    sendData(TxArr,1);
}

void UART::slotInit()
{
    if(PortInit("COM3"))
    {
        qDebug()<<"Port Opened!";
    }
    else
    {
        qDebug()<<"Port Failure!";
    }
}

void UART::slotClosePort()
{
    Port->close();
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
    return Port->open(QSerialPort::ReadWrite);
}

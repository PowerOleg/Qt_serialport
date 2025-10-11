#include "uart_controller.h"

Uart_controller::Uart_controller(QObject *parent)
    : QObject{parent}
{
    port = new QSerialPort(this);
    data = new Data(this);
    connect(port,&QSerialPort::readyRead,this,&Uart_controller::slotRead);
}

void Uart_controller::slotRead()
{
    QByteArray arr;
    arr.append(port->readAll());
    qDebug()<< "Data IN: "<< arr;
    emit sig_sendDataToScreen(arr);
    arr.clear();
}

void Uart_controller::slotEnableLed()
{
    TxArr.clear();
    TxArr.resize(0);
    TxArr.append(static_cast<char>(1));
    SendData(TxArr,1);
}

void Uart_controller::SendData(QByteArray Data, int length)
{
    qDebug()<<Data;
    if(Data.length() == length)
    {
        for(int i = 0;i<length;i++)
        {
            QByteArray temp;
            temp.resize(0);
            temp.append(Data[i]);
            port->write(temp);
            port->waitForBytesWritten();
            temp.clear();
        }
        Data.clear();
    }
}

void Uart_controller::slotDisableLed()
{
    TxArr.clear();
    TxArr.resize(0);
    TxArr.append(static_cast<char>(2));
    SendData(TxArr,1);
}

void Uart_controller::slotInit()
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

void Uart_controller::slotClosePort()
{
    port->close();
}

bool Uart_controller::PortInit(QString name)
{
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setPortName(name);
    port->close();//Закрываем порт
    return port->open(QSerialPort::ReadWrite);
}

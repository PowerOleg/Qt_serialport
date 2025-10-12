#include "uart_controller.h"

UartController::UartController(QObject *parent)
    : QObject{parent}
{
    port = new QSerialPort(this);
    dataFromArduino = new Data(this);
    connect(port,&QSerialPort::readyRead,this,&UartController::slotRead);
}

void UartController::slotRead()
{
    dataFromArduino->byteArray.clear();
    dataFromArduino->byteArray.append(port->readAll());//перенести в Data в метод set

    emit sig_sendDataToScreen(dataFromArduino);
    qDebug()<< "Data IN: "<< dataFromArduino->byteArray;
    //buffer->byteArray.clear();
    //qDebug()<< "Data cleared";
}

void UartController::slotEnableLed()
{
    QByteArray helloMessage;
    helloMessage.resize(0);
    helloMessage.append(static_cast<char>(1));
    SendData(helloMessage, 1);
}

void UartController::SendData(QByteArray &byteArray, int length)
{
    if(byteArray.length() == length)
    {
        for(int i = 0;i<length;i++)
        {
            QByteArray temp;
            temp.resize(0);
            temp.append(byteArray[i]);
            port->write(temp);
            port->waitForBytesWritten();
            temp.clear();
        }
        byteArray.clear();
    }
    qDebug()<< "sent: "<< dataFromArduino;
}

void UartController::slotDisableLed()
{
    QByteArray byeMessage;
    byeMessage.resize(0);
    byeMessage.append(static_cast<char>(2));
    SendData(byeMessage, 1);
}

void UartController::slotInit()
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
    port->setPortName(name);
    port->close();//Закрываем порт
    return port->open(QSerialPort::ReadWrite);
}

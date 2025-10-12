#ifndef UART_H
#define UART_H

#include <QObject>
#include <QtSerialPort>
#include <QDebug>
#include "../model/data.h"

class UartController : public QObject
{
    Q_OBJECT
public:
    QSerialPort* port;
    Data* dataFromArduino;
    explicit UartController(QObject *parent = nullptr);

private:
    bool PortInit(QString name);
    void SendData(QByteArray &byteArray, int length);
signals:
   void sig_sendDataToScreen(Data* data);
public slots:
    void slotRead();
    void slotEnableLed();
    void slotDisableLed();
    void slotInit();
    void slotClosePort();
};

#endif // UART_H

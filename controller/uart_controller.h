#ifndef UART_H
#define UART_H

#include <QObject>
#include <QtSerialPort>
#include <QDebug>
#include "../model/data.h"

class Uart_controller : public QObject
{
    Q_OBJECT
private:
    QByteArray TxArr;
    bool PortInit(QString name);
    void SendData(QByteArray Data,int length);
public:
    QSerialPort* port;
    Data* data;
    explicit Uart_controller(QObject *parent = nullptr);
signals:
   void sig_sendDataToScreen(QByteArray data);
public slots:
    void slotRead();
    void slotEnableLed();
    void slotDisableLed();
    void slotInit();
    void slotClosePort();
};

#endif // UART_H

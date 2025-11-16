#ifndef UART_H
#define UART_H

#include <QDebug>
#include <QObject>
#include <QtSerialPort>
#include "../model/data.h"
#include "../qcustomplot.h"

class UartController : public QObject
{
    Q_OBJECT
public:
    QSerialPort* port;
    Data* buffer;
    explicit UartController(QObject *parent = nullptr);
    ~UartController();

private:
    bool PortInit(QString name);
    void SendData(QByteArray &byteArray, int length);
signals:
//   void sendDataToScreen(const QByteArray &data);
public slots:
    void slotRead();
    void slotEnableLed();
    void slotDisableLed();
    void slotInit();
    void slotClosePort();
private:
    int receivedMessageSize = 2;
};

#endif // UART_H

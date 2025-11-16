#ifndef UART_H
#define UART_H

#include <QObject>
#include "qcustomplot.h"

class QSerialPort;

class UartController : public QObject
{
    Q_OBJECT
public:
    explicit UartController(QObject *parent = nullptr);
    ~UartController();
    QSerialPort* port;
private:
    bool PortInit(QString name);
    void SendData(QByteArray &byteArray, int length);
signals:
   void SendDataToScreen(const int x, const int y);
public slots:
    void SlotRead();
    void SlotEnable();
    void SlotDisableLed();
    void SlotInit();
    void SlotClosePort();
private:
    int receiveMessageSize = 2;
};

#endif // UART_H

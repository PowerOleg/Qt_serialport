#ifndef UART_H
#define UART_H

#include <QObject>
#include <QtSerialPort>
#include <QDebug>

class UART : public QObject
{
    Q_OBJECT
private:
    QByteArray TxArr;

    bool PortInit(QString name);
    void sendData(QByteArray Data,int length);
public:
    QSerialPort *Port;
    explicit UART(QObject *parent = nullptr);
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

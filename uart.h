#ifndef UART_H
#define UART_H

#include <QObject>
#include <QtSerialPort>

class UART : public QObject
{
    Q_OBJECT
private:
    bool PortInit(QString name);
    void sendData(QByteArray Data,int length);
    int Rxlength = 0;
    QByteArray RxArr;
    QByteArray TxArr;
public:
    explicit UART(QObject *parent = nullptr);
    QSerialPort *Port;
    void setRxLength(int length);
signals:
public slots:
    void slotRead();
    void slotEnableLed();
    void slotDisableLed();
    void slotInit();
};

#endif // UART_H

#ifndef UART_H
#define UART_H

#include <QObject>
#include <QtSerialPort>

class UART : public QObject
{
    Q_OBJECT
private:
    QSerialPort* Port; //Указатель на объект QSerialPort
    bool PortInit(QString name);
    void sendData(QByteArray Data,int length);
public:
    explicit UART(QObject *parent = nullptr);

signals:
    void slotRead();
};

#endif // UART_H

#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QByteArray>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);

    bool SetData(QByteArray byteArray);
    QByteArray GetData();
private:
    QByteArray byteArray;
};

#endif // DATA_H

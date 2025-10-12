#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QByteArray>
#include <QDebug>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);

    bool SetData(QByteArray &byteArray);
    bool CopyData(QByteArray byteArray);
    QByteArray GetData();
    bool Clear();
private:
    QByteArray byteArray;
};

#endif // DATA_H

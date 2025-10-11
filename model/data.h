#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QByteArray>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
    QByteArray TxArr;
};

#endif // DATA_H

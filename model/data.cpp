#include "data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{}

bool Data::SetData(QByteArray byteArray)
{
    this->byteArray.clear();
    this->byteArray.append(byteArray);
    return true;
}

QByteArray Data::GetData()
{
    return this->byteArray;
}

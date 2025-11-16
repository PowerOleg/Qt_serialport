#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QObject>
#include <QVector>
#include "qcustomplot.h"

#define FIRST_GRAPH 0

class Graphic : public QObject
{
    Q_OBJECT
public:
    Graphic(QCustomPlot* cPlot, uint32_t graphQuantity);

    void AddDataToGraph(QVector<double> &x, QVector<double> &y, uint32_t graphNumber);
    void ClearGraph(QCustomPlot* cPlot);
    void UpdateGraph(QCustomPlot *cPlot);

private:
    QVector<QCPGraph*> ptrGraph;
};

#endif // GRAPHIC_H

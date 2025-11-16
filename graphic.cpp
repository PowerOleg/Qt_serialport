#include <QMessageBox>
#include "graphic.h"

Graphic::Graphic(QCustomPlot* cPlot, uint32_t graphQuantity)
{
    ptrGraph.resize(graphQuantity);

    for (int i = 0; i < ptrGraph.size(); i++) {
        QCPGraph* graph = new QCPGraph(cPlot->xAxis, cPlot->yAxis);
        ptrGraph[i] = graph;
    }

    cPlot->setInteraction(QCP::iRangeZoom, true);
    cPlot->setInteraction(QCP::iRangeDrag, true);
}

void Graphic::AddDataToGraph(QVector<double> &x, QVector<double> &y, uint32_t graphNumber)
{
    if (graphNumber >= ptrGraph.size())
    {
        QMessageBox::information(nullptr, "Ошибка", "Неверный индекс линии графика для добавления точек");
        return;
    }
    if (x.size() != y.size())
    {
        QMessageBox::information(nullptr, "Ошибка", "Количество координат x не соответствует количеству координат y");
        return;
    }

    ptrGraph[graphNumber]->setData(x, y);
}

void Graphic::ClearGraph(QCustomPlot *cPlot)
{
    for (int i = 0; i < ptrGraph.size(); i++)
    {
        ptrGraph[i]->data()->clear();
    }

    for (int i = 0; i < cPlot->graphCount(); i++)
    {
        cPlot->graph(i)->data()->clear();
    }
    cPlot->replot();
}

void Graphic::UpdateGraph(QCustomPlot* cPlot)
{
    cPlot->rescaleAxes();
    cPlot->replot();
}

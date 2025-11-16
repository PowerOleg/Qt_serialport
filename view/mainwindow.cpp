#include <QDebug>
#include <QtSerialPort>
#include "../qcustomplot.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uartController = new UartController();
    thread = new QThread();
    graphClass = new Graphic(ui->customPlot, graphQuantity);

    connect(uartController, &UartController::SendDataToScreen, this, [=](const int x, const int y)
    {
        double doubleX = static_cast<double>(x);
        double doubleY = static_cast<double>(y);
        xVector.append(doubleX);
        yVector.append(doubleY);
        qDebug() << doubleX;
        qDebug() << doubleY;
    });
    connect(ui->btnRefresh, &QPushButton::clicked, this, [this]()
    {
        graphClass->AddDataToGraph(xVector, yVector, FIRST_GRAPH);
        graphClass->UpdateGraph(ui->customPlot);
    });
    connect(thread, &QThread::started, uartController, &UartController::SlotInit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    uartController->moveToThread(thread);
    uartController->port->moveToThread(thread);
    connect(ui->btnOn, &QPushButton::clicked, uartController, &UartController::SlotEnable, Qt::QueuedConnection);
    connect(ui->btnOff, &QPushButton::clicked, uartController, &UartController::SlotDisableLed, Qt::QueuedConnection);
    thread->start();
}

MainWindow::~MainWindow()
{
    delete uartController;
    delete ui;
    thread->quit();//поток удаляется через connect
}

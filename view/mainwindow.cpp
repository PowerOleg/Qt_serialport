#include <QDebug>
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





//    connect(uartController, &UartController::sendDataToScreen, this, [&](Data* receivedData)
//    {
//        ui->txtReadSerial->setText(receivedData->GetData());
//        //char *data = receiveData.data();
//        //int number = *data;
//        //ui->txtReadSerial->setText(QString::number(number));
    //    x.append(1.0);
    //    x.append(5.0);
    //    y.append(2.0);
    //    y.append(10.0);
        //    graphClass->AddDataToGraph(x, y, FIRST_GRAPH);

//    });
    connect(thread, &QThread::started, uartController, &UartController::slotInit);
    connect(thread, &QThread::finished, uartController, &UartController::slotClosePort);

    uartController->moveToThread(thread);
    uartController->port->moveToThread(thread);
    connect(ui->btnOn, &QPushButton::clicked, uartController, &UartController::slotEnableLed, Qt::QueuedConnection);
    connect(ui->btnOff, &QPushButton::clicked, uartController, &UartController::slotDisableLed, Qt::QueuedConnection);
    thread->start();
}

MainWindow::~MainWindow()
{
    delete uartController;
    thread->quit();
    if (thread->isFinished())
    {
        delete thread;
        delete ui;
    }
}

//void MainWindow::on_btnOn_clicked()
//{
//   uartController->slotEnableLed();
//}

//void MainWindow::on_btnOff_clicked()
//{
////    uartController->slotDisableLed();
//    ui->txtReadSerial->clear();
//}

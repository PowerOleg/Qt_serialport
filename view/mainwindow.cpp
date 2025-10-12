#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uartController = new UartController(this);
    thread = new QThread();

    connect(uartController, &UartController::sig_sendDataToScreen, this, [&](Data* receivedData)
    {
        ui->txtReadSerial->setText(receivedData->GetData());
        //char *data = receiveData.data();
        //int number = *data;
        //ui->txtReadSerial->setText(QString::number(number));
    });
    connect(thread, &QThread::started, uartController, &UartController::slotInit);
    connect(thread, &QThread::finished, uartController, &UartController::slotClosePort);
    uartController->moveToThread(thread);
    uartController->port->moveToThread(thread);
    thread->start();
}

MainWindow::~MainWindow()
{
    thread->quit();
    if (thread->isFinished())
    {
        delete thread;
        delete ui;
    }
}

void MainWindow::on_btnOn_clicked()
{
   uartController->slotEnableLed();
}

void MainWindow::on_btnOff_clicked()
{
    uartController->slotDisableLed();
    ui->txtReadSerial->clear();
}

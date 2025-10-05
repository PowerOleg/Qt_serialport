#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    com = new UART();//where this argument?
    thr = new QThread();

    connect(com, &UART::sig_sendDataToScreen, this, [=](QByteArray receiveData)
    {
        //char *data = receiveData.data();
        //int number = *data;
        //ui->txtReadSerial->setText(QString::number(number));
        ui->txtReadSerial->setText(receiveData);
    });
    connect(thr,&QThread::started,com,&UART::slotInit);
    connect(thr,&QThread::finished,com,&UART::slotClosePort);
    com->moveToThread(thr);
    com->Port->moveToThread(thr);
    thr->start();
}

MainWindow::~MainWindow()
{
    thr->quit();
    delete com;
    if(thr->isFinished())
    {
        delete thr;
        delete ui;
    }
}

void MainWindow::on_btnOn_clicked()
{
   com->slotEnableLed();
}

void MainWindow::on_btnOff_clicked()
{
    com->slotDisableLed();
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    com = new UART();//where this argument?
    thr = new QThread();

    connect(thr,&QThread::started,com,&UART::slotInit);//Открываем порт
    //connect(ui->pushButton,&QPushButton::clicked,com,&UART::slotEnableLed);//TODO
    //connect(ui->pushButton_2,&QPushButton::clicked,com,&UART::slotDisableLed);//TODO
    connect(thr,&QThread::finished,com,&UART::slotClosePort);//Закрываем порт
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

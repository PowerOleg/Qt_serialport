#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    com = new UART();
    thr = new QThread();

    connect(thr,&QThread::started,com,&UART::slotInit);//Открываем порт
    connect(ui->pushButton,&QPushButton::clicked,com,&UART::slotEnableLed);//Соединяем кнопку ВКЛ
    connect(ui->pushButton_2,&QPushButton::clicked,com,&UART::slotDisableLed);//Соединяем кнопку ВЫКЛ
    com->moveToThread(thr);
    com->Port->moveToThread(thr);//041025
}

MainWindow::~MainWindow()
{
    delete ui;
}


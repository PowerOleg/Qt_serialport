#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QVector>
#include <QtSerialPort>
#include "../controller/uart_controller.h"
#include "../qcustomplot.h"
#include "../graphic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    UartController *uartController;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QThread *thread;
    QVector<double> x, y;
    Graphic* graphClass;
    uint32_t graphQuantity = 1;
};
#endif // MAINWINDOW_H

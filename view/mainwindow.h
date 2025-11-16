#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QThread>
#include <QVector>
#include "../controller/uart_controller.h"
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
    QVector<double> xVector, yVector;
    Graphic* graphClass;
    uint32_t graphQuantity = 1;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QTcpSocket>
#include<chatwindow.h>
#include<string.h>
#include"package.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket* send;
     chatwindow* cw;
private slots:
    void mainwindowread();
    void on_pushreg_clicked();
    void on_pushlogin_clicked();
signals:
     void chatwindowsignal(pack);
     void chatwindow_privatechatwindowsignal(pack);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

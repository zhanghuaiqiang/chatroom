#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"sockethelper.h"
#include"package.h"
#include<vector>
#include<QDebug>
#include<QMap>
using namespace  std;
std::vector <sockethelper*> v;//�洢��ͬ��sockethelper����ָ��
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server=new QTcpServer(this);
    qRegisterMetaType<pack>("pack");
    connect(server,SIGNAL(newConnection()),this,SLOT(onnewconnection()));

}
void MainWindow::onnewconnection()
{
    QTcpSocket*socket=server->nextPendingConnection();
    sockethelper* cm=new sockethelper(socket);//����ͬsoket��װ��һ����
    v.push_back(cm);
    connect(socket,SIGNAL(disconnected()),cm,SLOT(ondisconnect()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushlisten_clicked()//����������
{
    server->listen(QHostAddress("127.0.0.1"),8890);
    if(server->isListening())
    {
        ui->label->setText("listening...");
    }
}

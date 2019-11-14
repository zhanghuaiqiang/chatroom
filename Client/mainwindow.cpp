#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHostAddress>
#include"package.h"
#include<QMessageBox>
#include<iostream>
using namespace  std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    send=new QTcpSocket(this);
    send->connectToHost(QHostAddress("127.0.0.1"),8890);
    qRegisterMetaType<pack>("pack");
    connect(send,SIGNAL(readyRead()),this,SLOT(mainwindowread()));
}
void MainWindow::mainwindowread()
{
    pack packreg;
    memset(packreg.allname,'\0',sizeof(packreg.allname));
    send->read((char*)&packreg,sizeof(pack));
    if(packreg.selectwindow==CHATWINDOW)
    {
        emit chatwindowsignal(packreg);
    }
    if(packreg.selectwindow==PRIVATECHATWINDOW)
    {
        emit chatwindow_privatechatwindowsignal(packreg);
    }
    switch(packreg.type)
    {

        case REGSUCCESS_TYPE:
        {
            QMessageBox::information(this,"register","success");
        }break;
        case REGFAIL_TYPE:
        {
            QMessageBox::information(this,"register","fail");
        }break;
        case LOGSUCCESS_TYPE:
        {
            hide();
            cw =new chatwindow(send,packreg.name,this);
            cw->show();
        }break;
        case LOGFAIL_TYPE:
        {
            QMessageBox::information(this,"login","fail");
        }break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushreg_clicked()
{
    QString qName=ui->linename->text();
    QString qPwd=ui->linepwd->text();
    struct pack packreg;
    packreg.type =1;
    strcpy(packreg.name,qName.toLatin1().data());
    strcpy(packreg.pwd,qPwd.toLatin1().data());
    send->write((char*)&packreg,sizeof(packreg));
}

void MainWindow::on_pushlogin_clicked()
{
    QString qName=ui->linename->text();
    QString qPwd=ui->linepwd->text();
    struct pack packreg;
    packreg.type =Log_TYPE;
    strcpy(packreg.name,qName.toLatin1().data());
    strcpy(packreg.pwd,qPwd.toLatin1().data());
    send->write((char*)&packreg,sizeof(packreg));
}




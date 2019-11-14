#include "privatechatwindow.h"
#include "ui_privatechatwindow.h"
#include "mainwindow.h"
#include<QHostAddress>
#include"package.h"
#include"qdebug.h"
#include<iostream>
#include "chatwindow.h"
using namespace  std;

privatechatwindow::privatechatwindow(QTcpSocket*cwsend,char*selname,char*selectlistname,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::privatechatwindow)
{
    ui->setupUi(this);
    pwsend= cwsend;
    QString st;
    st= QString::fromUtf8(selname);
    ui->label_2name->setText(st);
    strcpy(selfname,selname);
    strcpy(pwselectlistcname,selectlistname);
    qRegisterMetaType<pack>("pack");

   chatwindow * privatecw=(chatwindow*)parentWidget();

    connect(privatecw,SIGNAL(privatechatwindowsignal(pack)),this,SLOT(privatechatread(pack)));
}

privatechatwindow::~privatechatwindow()
{
    delete ui;
}

void privatechatwindow::privatechatread(pack pa)
{

    pack chatpack;
    chatpack=pa;
    switch(chatpack.type)
    {
    case PRIVATEDATA_TYPE:
    {
        ui->textEdit->append(chatpack.dataname);
        ui->textEdit->QTextEdit::setAlignment(Qt::AlignLeft);
        ui->textEdit->append(chatpack.privatedate);
        ui->textEdit->QTextEdit::setAlignment(Qt::AlignLeft);
    }
        break;
    }
}
void privatechatwindow::on_pushButton_clicked()
{
    QString chat = ui->lineEdit->text();
    struct pack datapack;
    datapack.type =PRIVATEDATA_TYPE;
    datapack.selectwindow=PRIVATECHATWINDOW;
    strcpy_s(datapack.dataname,pwselectlistcname);
    strcpy_s(datapack.privatedate,chat.toLatin1().data());
    ui->lineEdit->setText("");
    ui->textEdit->append(selfname);
    ui->textEdit->QTextEdit::setAlignment(Qt::AlignRight);
    ui->textEdit->append(datapack.privatedate);
    ui->textEdit->QTextEdit::setAlignment(Qt::AlignRight);
    pwsend->write((char*)&datapack,sizeof(pack));

}

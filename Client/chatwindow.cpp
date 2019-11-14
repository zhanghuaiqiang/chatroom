#include "chatwindow.h"
#include "ui_chatwindow.h"

#include<string>
#include<QDebug>
#include<iostream>
#include"mainwindow.h"
#include"QListWidgetItem"
#include "privatechatwindow.h"
#include<QString>


using namespace std;

chatwindow::chatwindow(QTcpSocket* msend,char*name,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);
    cwsend=msend;
    strcpy_s(logsuname,name);
    QString st;
    st= QString::fromUtf8(name);
    ui->label_member->setText(st);
    qRegisterMetaType<pack>("pack");
    MainWindow * chatmw = (MainWindow*)parentWidget();
    //connect(cwsend,SIGNAL(readyRead()),this,SLOT(chatread()));
    connect(chatmw,SIGNAL(chatwindowsignal(pack)),this,SLOT(chatread(pack)));
    connect(chatmw,SIGNAL(chatwindow_privatechatwindowsignal(pack)),this,SLOT(toprivatechatread(pack)));
}

void chatwindow::toprivatechatread(pack toprivatepack)
{
    emit privatechatwindowsignal(toprivatepack);
}

chatwindow::~chatwindow()
{
    delete ui;
}
void chatwindow::chatread(pack pa)
{
        pack chatpack;
        memset(chatpack.allname,'\0',sizeof(chatpack.allname));
        chatpack=pa;

        switch(chatpack.type)
        {
        case LIST_TYPE:
        {
            ui->listWidget->clear();
            ui->label_count->setText(QString::number(chatpack.size));
            strcpy_s(connectname,chatpack.allname);
            char* token = strtok( connectname, ",");
            while( token != nullptr )
            {
                QListWidgetItem*item=new QListWidgetItem;
                item->setText(token);
                ui->listWidget->addItem(item);
                token = strtok( nullptr, ",");
            }

        }break;
        case PRIVATE_TYPE:
        {
            privatechatwindow* pw = new privatechatwindow(cwsend,logsuname,chatpack.name,this);
            pw->show();
        }break;
        case CHAT_TYPE:
        {
            ui->textEdit->append(chatpack.name);
            ui->textEdit->append(chatpack.data);
            ui->textEdit->QTextEdit::setAlignment(Qt::AlignLeft);
        }break;
        default:
            break;
        }
}


void chatwindow::on_pushButton_clicked()//ÈºÁÄsend°´Å¥
{
    QString chat = ui->lineEdit->text();
    struct pack chatpack;
    chatpack.selectwindow=CHATWINDOW;
    chatpack.type =CHAT_TYPE;
    chatpack.selectwindow=CHATWINDOW;
    strcpy_s(chatpack.name,logsuname);
    strcpy_s(chatpack.data,chat.toLatin1().data());
    cwsend->write((char*)&chatpack,sizeof(pack));
    ui->lineEdit->setText("");
}


void chatwindow::showEvent(QShowEvent*event)
{
    ui->listWidget->clear();
    struct pack onlinepack;
    onlinepack.type =LIST_TYPE;
    onlinepack.selectwindow=CHATWINDOW;
    cwsend->write((char*)&onlinepack,sizeof(pack));
}

void chatwindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    strcpy_s(cwlistselectname,item->text().toLatin1().data());
    struct pack privatepack;
    privatepack.selectwindow=CHATWINDOW;
    privatepack.type=PRIVATE_TYPE;
    strcpy_s(privatepack.privatename,item->text().toLatin1().data());
    privatechatwindow* sw = new privatechatwindow(cwsend,logsuname,cwlistselectname,this);
    sw->show();
    cwsend->write((char*)&privatepack,sizeof(pack));


}

void chatwindow::on_pushButtoncloseflush_clicked()
{
    ui->listWidget->clear();
    struct pack onlinepack;
    onlinepack.type =LIST_TYPE;
    onlinepack.selectwindow=CHATWINDOW;
    cwsend->write((char*)&onlinepack,sizeof(pack));
}

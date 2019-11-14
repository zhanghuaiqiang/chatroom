#ifndef PRIVATECHATWINDOW_H
#define PRIVATECHATWINDOW_H

#include <QDialog>
#include<QTcpSocket>
#include"package.h"

namespace Ui {
class privatechatwindow;
}

class privatechatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit privatechatwindow(QTcpSocket*,char*,char*,QWidget *parent );
    ~privatechatwindow();
   QTcpSocket* pwsend;
    char pwselectlistcname[30];
    char selfname[30];

private slots:
    void on_pushButton_clicked();
    void privatechatread(pack);

private:
    Ui::privatechatwindow *ui;
};

#endif // PRIVATECHATWINDOW_H

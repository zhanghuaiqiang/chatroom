#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include<QTcpSocket>
#include<QMessageBox>
#include"package.h"
#include"QListWidgetItem"
#include "privatechatwindow.h"
#include"QShowEvent"


namespace Ui {
class chatwindow;
}

class chatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit chatwindow(QTcpSocket *,char *,QWidget *parent );
    ~chatwindow();
    QTcpSocket* cwsend;
    char logsuname[30];
    char cwlistselectname[30];
    char connectname[300];



protected:
    void showEvent(QShowEvent*);

signals:
    void privatechatwindowsignal(pack);
private slots:
    void on_pushButton_clicked();
    void chatread(pack);
    void toprivatechatread(pack);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButtoncloseflush_clicked();

private:
    Ui::chatwindow *ui;
};

#endif // CHATWINDOW_H

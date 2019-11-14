#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H
#include"package.h"
#include <QObject>
#include<QTcpSocket>
class sockethelper : public QObject
{
    Q_OBJECT
public:
    explicit sockethelper(QTcpSocket* s,QObject *parent = 0);
    QTcpSocket* socket;
    void loginuser(pack packreg);
    void listmember(pack packreg);
    void privatemember(pack packreg);
    void privatadata(pack packreg);
    void flushlist();
    char logsucname[30];
signals:
public slots:
    void onread();
    void ondisconnect();
    void chat_fun(pack packreg);
};

#endif // SOCKETHELPER_H

#ifndef DBHELPER_H
#define DBHELPER_H
#include<QMutex>
#include<QSqlDatabase>
//����ģʽ��װ���ݿ�
class dbhelper
{
private:
    dbhelper();
    static dbhelper* instance;
    static QMutex mu;
    QSqlDatabase db;
public:
    static dbhelper* getinstance();
    void createconnect();
    void removeconnect();
    bool insertuser(char* name,char* pwd);
    bool checkuser(char* name,char* pwd);
};

#endif // DBHELPER_H

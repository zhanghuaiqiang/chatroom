#include "dbhelper.h"
#include<QSqlQuery>
#include<stdio.h>
dbhelper* dbhelper::instance=0;
QMutex dbhelper::mu;
dbhelper::dbhelper()//数据库封装
{
    db=QSqlDatabase::addDatabase("QSQLITE");
}
dbhelper* dbhelper::getinstance()
{
    mu.lock();
    if(instance==0)
    {
        instance=new dbhelper;
    }
    mu.unlock();
    return instance;
}
void dbhelper::createconnect()//数据库连接打开
{
    db.setDatabaseName("user.db");
    db.open();
}

void dbhelper::removeconnect()//数据库关闭
{
    db.close();db.removeDatabase("user.db");
}
bool dbhelper::insertuser(char* name,char* pwd)//数据库插入用户
{
    createconnect();
    QSqlQuery query(db);
    char sqldata[1024]={0};
    sprintf(sqldata,"insert into user values ('%s','%s');",name,pwd);
    bool ret=query.exec(sqldata);
    removeconnect();
    return ret;
}
bool dbhelper::checkuser(char* name,char* pwd)//数据库查找比对用户
{
    createconnect();
    QSqlQuery query(db);
    char sqldata[1024]={0};
    sprintf(sqldata,"select * from user where name = '%s' and pwd = '%s';",name,pwd);
    query.exec(sqldata);
    bool ret=query.next();
    removeconnect();
    return ret;
}





#include "sockethelper.h"
#include"package.h"
#include<QDebug>
#include "dbhelper.h"
#include<vector>

#include<string.h>
using namespace std;
extern vector <sockethelper*> v;

sockethelper::sockethelper(QTcpSocket *s, QObject *parent) : QObject(parent)
{

    socket=s;
    memset(logsucname,'\0',sizeof(logsucname));
    connect(socket,SIGNAL(readyRead()),this,SLOT(onread()));
}
void sockethelper::onread()
{
    pack packreg;
    memset(packreg.allname,'\0',sizeof(packreg.allname));
    socket->read((char*)&packreg,sizeof(pack));
    switch(packreg.type)
    {
            case REGISTER_TYPE:
            {
                pack pa;
                bool ret=dbhelper::getinstance()->insertuser(packreg.name,packreg.pwd);
                if(ret)
                {
                    pa.type=REGSUCCESS_TYPE;

                }
                else
                {
                    pa.type=REGFAIL_TYPE;
                }
                memset(pa.allname,'\0',sizeof(pa.allname));
                socket->write((char*)&pa,sizeof(pa));
            }
                break;
            case Log_TYPE:
                loginuser(packreg);
                break;
            case CHAT_TYPE:
                chat_fun(packreg);
                break;
             case LIST_TYPE:
                listmember(packreg);
                break;
             case PRIVATE_TYPE:
                 privatemember(packreg);
                break;
            case PRIVATEDATA_TYPE:
                privatadata(packreg);
                break;
    }
}


void sockethelper::ondisconnect()
{
    vector<sockethelper*>::iterator it;
    for(it=v.begin();it!=v.end();it++)
    {
        if((*it)->socket==this->socket)
        {
            v.erase(it);deleteLater();break;
        }
    }
}



void sockethelper::loginuser(pack packreg)
{
    //int m=0;int n=0;
    pack pa;
     memset(pa.allname,'\0',sizeof(pa.allname));
    bool ret=dbhelper::getinstance()->checkuser(packreg.name,packreg.pwd);
    if(ret)
    {

        pa.type=LOGSUCCESS_TYPE;

        strcpy_s(pa.name,packreg.name);
        strcpy_s(logsucname,packreg.name);
        //ºó¸ÄµÄ
    }
    else
    {
        pa.type=LOGFAIL_TYPE;
    }
    socket->write((char*)&pa,sizeof(pa));


}
void sockethelper::chat_fun(pack packreg)
{
    vector<sockethelper*>::iterator userit=v.begin();
     for(;userit!=v.end();userit++)

    {
         memset(packreg.allname,'\0',sizeof(packreg.allname));
         (*userit)->socket->write((char*)&packreg,sizeof(packreg));
     }
}

 void sockethelper::listmember(pack packreg)
 {
     memset(packreg.allname,'\0',sizeof(packreg.allname));
     vector <sockethelper*>::iterator it;
     int count=0;
     for (it= v.begin();it!=v.end();it++)
     {
         if(!((*it)->logsucname[0]=='\0'))
         {
             strcat_s(packreg.allname,(*it)->logsucname);
             strcat_s(packreg.allname,",");
             count++;
         }
     }
     packreg.size=count;
     //qDebug()<<"packreg.allname =="<<packreg.allname<<endl;
     vector <sockethelper*>::iterator itt;
     packreg.type=LIST_TYPE;
     packreg.selectwindow=CHATWINDOW;
     for (itt= v.begin();itt!=v.end();itt++)
     {
         if(!((*itt)->logsucname[0]=='\0'))
         {
             (*itt)->socket->write((char*)&packreg,sizeof(pack));

         }
     }
     // qDebug()<<"packreg.allname ==="<<packreg.allname<<endl;
 }


 void sockethelper::privatemember(pack packreg)
 {
     pack pa;
     memset(packreg.allname,'\0',sizeof(packreg.allname));
     pa.type=PRIVATE_TYPE;
     pa.selectwindow=CHATWINDOW;
     strcpy(pa.privatename,packreg.privatename);
     vector <sockethelper*>::iterator it;
      strcpy(pa.name,logsucname);
     for (it= v.begin();it!=v.end();it++)
     {
         //((*it)->logsucname,packreg.privatename);
         if(!strcmp((*it)->logsucname,packreg.privatename))
         {
             (*it)->socket->write((char*)&pa,sizeof(pack));
         }
     }
 }

 void sockethelper::privatadata(pack packreg)
 {
     pack pa;
     memset(packreg.allname,'\0',sizeof(packreg.allname));
     pa.type=PRIVATEDATA_TYPE;
     pa.selectwindow=PRIVATECHATWINDOW;
     vector <sockethelper*>::iterator it;
     strcpy(pa.privatedate,packreg.privatedate);

     strcpy(pa.dataname,logsucname);


     for (it= v.begin();it!=v.end();it++)
     {
         if(!strcmp((*it)->logsucname,packreg.dataname))
         {
             (*it)->socket->write((char*)&pa,sizeof(pack));
         }
     }
 }

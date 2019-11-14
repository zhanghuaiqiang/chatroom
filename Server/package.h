#ifndef PACKAGE_H
#define PACKAGE_H
#include <QMetaType>
enum datetype
{
    REGISTER_TYPE=1,
    REGFAIL_TYPE,
    REGSUCCESS_TYPE,
    Log_TYPE,
    LOGFAIL_TYPE,
    LOGSUCCESS_TYPE,
    CHAT_TYPE,
    LIST_TYPE,
    PRIVATE_TYPE,
    PRIVATEDATA_TYPE,
    CHATWINDOW,
    PRIVATECHATWINDOW
};
struct pack
{
    int selectwindow;
    int type;
    int size;
    char name[80];
    char privatename[80];
    char dataname[80];
    char pwd[80];
    char data[3000];
    char privatedate[3000];
    char allname[3000];
};
Q_DECLARE_METATYPE(pack);//×¢²ápack
#endif // PACKAGE_H

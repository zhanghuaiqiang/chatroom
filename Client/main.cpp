#include "mainwindow.h"
#include <QApplication>
#include"package.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qRegisterMetaType<pack>("pack");
    return a.exec();
}

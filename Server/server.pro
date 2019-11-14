#-------------------------------------------------
#
# Project created by QtCreator 2019-07-30T21:14:26
#
#-------------------------------------------------

QT       += core gui
QT+=network
QT+=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled9
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sockethelper.cpp \
    dbhelper.cpp

HEADERS  += mainwindow.h \
    sockethelper.h \
    package.h \
    dbhelper.h

FORMS    += mainwindow.ui

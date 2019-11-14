#-------------------------------------------------
#
# Project created by QtCreator 2019-07-30T21:14:05
#
#-------------------------------------------------

QT       += core gui
QT+=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled8
TEMPLATE = app


SOURCES += main.cpp\
        chatwindow.cpp \
        mainwindow.cpp \
        privatechatwindow.cpp

HEADERS  += mainwindow.h \
    chatwindow.h \
    package.h \
    privatechatwindow.h

FORMS    += mainwindow.ui \
    chatwindow.ui \
    privatechatwindow.ui

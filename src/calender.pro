#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T10:09:45
#
#-------------------------------------------------

QT       += core gui
QT       += xml
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    littlewidget.cpp \
    block.cpp \
    eventdata.cpp \
    eventhandler.cpp \
    form.cpp \
    clicklabel.cpp \
    draglabel.cpp \
    dialogwidget.cpp \
    loginhandler.cpp \
    loginwidget.cpp

HEADERS  += mainwindow.h \
    littlewidget.h \
    block.h \
    eventdata.h \
    eventhandler.h \
    form.h \
    clicklabel.h \
    draglabel.h \
    dialogwidget.h \
    loginhandler.h \
    loginwidget.h

FORMS    += mainwindow.ui \
    littlewidget.ui \
    block.ui \
    form.ui \
    dialogwidget.ui \
    loginwidget.ui

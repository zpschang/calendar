#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T10:09:45
#
#-------------------------------------------------

QT       += core gui
QT       += xml
CONFIG   += c++11
TRANSLATIONS += tr_chinese.ts \
                 tr_english.ts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calendar
TEMPLATE = app


SOURCES += main.cpp\
    littlewidget.cpp \
    block.cpp \
    eventdata.cpp \
    eventhandler.cpp \
    form.cpp \
    clicklabel.cpp \
    draglabel.cpp \
    dialogwidget.cpp \
    loginhandler.cpp \
    loginwidget.cpp \
    calendar.cpp

HEADERS  += \
    littlewidget.h \
    block.h \
    eventdata.h \
    eventhandler.h \
    form.h \
    clicklabel.h \
    draglabel.h \
    dialogwidget.h \
    loginhandler.h \
    loginwidget.h \
    calendar.h

FORMS    += \
    littlewidget.ui \
    block.ui \
    form.ui \
    dialogwidget.ui \
    loginwidget.ui \
    calendar.ui

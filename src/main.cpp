#include "calendar.h"
#include <QApplication>
#include <QCalendarWidget>
#include <QTimer>
#include <QDebug>
#include <QTranslator>
#include "eventhandler.h"
#include "loginhandler.h"
int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("/Users/pushi/GitHub/calendar/src/tr_chinese.qm");
    a.installTranslator(&translator);
    EventHandler handler;
    LoginHandler login_handler;
    Calendar *calendar = new Calendar(handler, login_handler, false);

    //w.setAutoFillBackground(true);



    return a.exec();
}

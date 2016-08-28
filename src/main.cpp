#include "mainwindow.h"
#include <QApplication>
#include <QCalendarWidget>
#include <QTimer>
#include <QDebug>
#include "eventhandler.h"
#include "loginhandler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EventHandler handler;
    LoginHandler login_handler;
    MainWindow w(handler, login_handler);
    w.setWindowFlags(Qt::FramelessWindowHint);
    //w.setWindowOpacity(1);
    w.setAttribute(Qt::WA_TransparentForMouseEvents);
    w.show();
    //w.setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255, 255));
    w.setPalette(palette);

    return a.exec();
}

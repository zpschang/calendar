#include "mainwindow.h"
#include <QApplication>
#include <QCalendarWidget>
#include <QTimer>
#include <QDebug>
#include "eventhandler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    EventHandler handler;
    EventData event;
    event.name = "事件";
    event.description = "aaa";
    event.start_date.setDate(2016, 8, 27);
    event.start_time = QTime(15, 0);
    event.end_time = QTime(15, 45);
    event.repeat_style = EventData::Month;
    event.maxi_index = 5;
    event.number = 1;
    event.deleted_index.insert(3);
    qDebug() << event.is_in(QDate(2016, 10, 27));
    handler.events.push_back(&event);
    handler.user_name = "zpschang";
    handler.write_data();
    EventData *_event = handler.events[0];
    _event->is_in(QDate(2016, 8, 23));
    MainWindow w(handler);
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

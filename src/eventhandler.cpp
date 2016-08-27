#include "eventhandler.h"
#include <QIODevice>
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
EventHandler::EventHandler()
{

}

QString EventHandler::read_data(QString _user_name)
{
    events.clear();
    user_name = _user_name;
    QString file_name = "user_" + user_name + ".data";
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
        return "file not found";
    while(!file.atEnd())
    {
        EventData *event = new EventData;
        file.read((char*)event, sizeof(EventData));
        events.push_back(event);
    }
    file.close();
    return "success";
}

void EventHandler::write_data()
{
    QString file_name = "user_" + user_name + ".data";
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    for(int i = 0; i < events.size(); i++)
        file.write((char*)events[i], sizeof(EventData));
    file.close();
}

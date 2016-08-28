#include "eventhandler.h"
#include <QIODevice>
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
EventHandler::EventHandler()
{
    file_name = "autosaved.data";
}

EventHandler::~EventHandler()
{
    write_data(file_name);
}

QString EventHandler::read_data(QString file_name)
{
    this->file_name = file_name;
    events.clear();
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
        return "file not found";
    QDataStream in(&file);
    QString _user, _password;
    in >> _user >> _password;
    if(user != _user)
        return "not same user";
    if(password != _password)
        return "not same password";
    int size;
    in >> size;
    for(int i = 0; i < size; i++)
    {
        EventData *event = new EventData;
        events.push_back(event);
        in >> event->name >> event->description;
        in >> event->start_date >> event->start_time >> event->end_time;
        in >> (qint32&)event->repeat_style >> (qint32&)event->maxi_index >> (qint32&)event->number;
        in >> event->color;
        int size_del;
        in >> size_del;
        for(int j = 0; j < size_del; j++)
        {
            int data;
            in >> data;
            event->deleted_index.insert(data);
        }
        int size_file;
        in >> (qint32&)size_file;
        for(int j = 0; j < size_file; j++)
        {
            QString str;
            in >> str;
            event->file_path.push_back(str);
        }
    }
    return "success";
}

void EventHandler::write_data(QString file_name)
{
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << user << password;
    out << (int)events.size();
    for(EventData *event : events)
    {
        out << event->name << event->description;
        out << event->start_date << event->start_time << event->end_time;
        out << (int)event->repeat_style << event->maxi_index << event->number;
        out << event->color;
        out << (int)event->deleted_index.size();
        for(int index : event->deleted_index)
            out << index;
        out << (int)event->file_path.size();
        for(QString str : event->file_path)
            out << str;
    }
    file.close();
}

void EventHandler::merge(EventHandler &handler)
{
    for(EventData *event : handler.events)
        events.push_back(event);
}

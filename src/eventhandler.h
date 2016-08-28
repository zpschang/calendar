#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include "eventdata.h"
using namespace std;
class EventHandler
{
public:
    vector<EventData *> events;
    QString user, password, file_name;
    EventHandler();
    ~EventHandler();
    QString read_data(QString);
    void write_data(QString);
    void merge(EventHandler &);
};

#endif // EVENTHANDLER_H

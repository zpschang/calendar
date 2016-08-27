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
    QString user_name;
    EventHandler();
    QString read_data(QString _user_name);
    void write_data();
};

#endif // EVENTHANDLER_H

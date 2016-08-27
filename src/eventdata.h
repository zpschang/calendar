#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <QDate>
#include <QTime>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
class EventData
{
public:
    QDate start_date;
    enum RepeatCycle{None=0, Day=1, Week=2, Month=3, Year=4};
    RepeatCycle repeat_style;
    int maxi_index;
    int number;
    QString name, description;
    vector<QString> file_path;
    QTime start_time, end_time;
    set<int> deleted_index;
    void del_day(int index);
    void del_day_after(int index);
    int is_in(QDate date);
    bool is_empty();
};

#endif // EVENTDATA_H

#include "eventdata.h"
#include <QDebug>
void EventData::del_day(int index)
{
    deleted_index.insert(index);
}

void EventData::del_day_after(int index)
{
    maxi_index = index;
    auto pt = lower_bound(deleted_index.begin(), deleted_index.end(), index);
    deleted_index.erase(pt, deleted_index.end());
}

int EventData::is_in(QDate date)
{
    if(repeat_style == None)
        return date == start_date ? 0 : -1;

    if(repeat_style == Day)
    {
        int days = start_date.daysTo(date);

        if(days % number != 0)
            return -1;
        int temp = days / number;
        for(int index : deleted_index)
            if(index == temp)
                return -1;
        return (temp >= 0 && (temp < maxi_index || maxi_index == -1)) ? temp : -1;
    }
    if(repeat_style == Week)
    {
        int days = start_date.daysTo(date);
        if(days % (7*number) != 0)
            return -1;
        int temp = days / (7*number);
        for(int index : deleted_index)
            if(index == temp)
                return -1;
        return (temp >= 0 && (temp < maxi_index || maxi_index == -1)) ? temp : -1;
    }
    if(repeat_style == Month)
    {
        QDate now = start_date;
        int i;
        for(i = 0; now < date; i++)
        {
            if(i >= maxi_index && maxi_index != -1)
                return -1;
            now = start_date.addMonths(number * (i+1));
        }
        if(now != date)
            return -1;
        for(int index : deleted_index)
            if(index == i)
                return -1;
        return i;
    }
    if(repeat_style == Year)
    {
        QDate now = start_date;
        int i;
        for(i = 0; now < date; i++)
        {
            if(i >= maxi_index && maxi_index != -1)
                return -1;
            now = start_date.addYears(number * (i+1));
        }
        if(now != date)
            return -1;
        for(int index : deleted_index)
            if(index == i)
                return -1;
        return i;
    }
    return -1;
}

bool EventData::is_empty()
{
    bool flag = true;
    for(int i = 0; i < maxi_index; i++)
        if(deleted_index.find(i) == deleted_index.end())
            flag = false;
    return flag;
}

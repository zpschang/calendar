#include "loginhandler.h"
#include <QDebug>
LoginHandler::LoginHandler()
{
    QFile file("user_data/data");
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        int size;
        in >> (qint32&)size;
        for(int i = 0; i < size; i++)
        {
            QString user, password;
            in >> user >> password;
            m_map[user] = password;
        }
        file.close();
    }
}

LoginHandler::~LoginHandler()
{
    QDir dir;
    dir.mkdir("user_data");
    QFile file("./user_data/data");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << (int)m_map.size();
        for(auto i = m_map.begin(); i != m_map.end(); i++)
            out << i->first << i->second;
        file.close();
    }
    else
        qDebug() << "aaaaaa";
}

QString LoginHandler::regist(QString user, QString password)
{
    if(m_map.find(user) != m_map.end())
        return "username is occupied";
    m_map[user] = password;
    return "success";
}

QString LoginHandler::login(QString user, QString password)
{
    if(m_map.find(user) == m_map.end())
        return "username is not registered";
    if(m_map[user] != password)
        return "wrong password";
    return "success";
}

#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include <QString>
#include <map>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QDataStream>
using namespace std;
class LoginHandler
{
    map<QString, QString> m_map;
public:
    LoginHandler();
    ~LoginHandler();
    QString regist(QString, QString);
    QString login(QString, QString);
};

#endif // LOGINHANDLER_H

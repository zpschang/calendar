#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT
signals:
    void login(QString, QString);
    void regist(QString, QString);
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H

#ifndef Calendar_H
#define Calendar_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>
#include <QDebug>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMenuBar>
#include <QPainter>
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QTranslator>
#include "block.h"
#include "littlewidget.h"
#include "eventhandler.h"
#include "loginwidget.h"
#include "loginhandler.h"
namespace Ui {
class Calendar;
}

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calendar(EventHandler &, LoginHandler &, bool, QWidget *parent = 0);
    EventHandler &handler;
    LoginHandler &login_handler;
    ~Calendar();

private:
    Ui::Calendar *ui;
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout[8];
    QPushButton *btn_prev, *btn_next, *btn_fix;
    QLabel *txt_mid;
    QLabel *txt_date[7];
    QLabel *txt_user;
    Block *block[7][7];
    LittleWidget *little_widget;
    LoginWidget *login_widget;
    int year, month;
    static QString str_date[7];
    QPoint pointer;
    bool is_clicked, is_fixed;
    QString user, password;

    void update_month();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    bool eventFilter(QObject *, QEvent *);
    void slot(bool, Block *);
};

#endif // Calendar_H

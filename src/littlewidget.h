#ifndef LITTLEWIDGET_H
#define LITTLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QDate>
#include <map>
#include <vector>
#include <QMenu>
#include <QFocusEvent>
#include "eventhandler.h"
#include "form.h"
#include "clicklabel.h"
#include "dialogwidget.h"
using namespace std;

namespace Ui {
class LittleWidget;
}

class LittleWidget : public QWidget
{
    Q_OBJECT
signals:
    void close_signal(bool);
public:
    EventHandler &handler;
    explicit LittleWidget(EventHandler &_handler, QDate _date, QWidget *parent = 0);
    QLabel *label;
    QPushButton *btn, *btn_add;
    bool is_clicked;
    QPoint pointer;
    QDate date;
    QWidget *menu_window;
    Form *form;
    DialogWidget *dialog;
    map<QWidget*, pair<EventData*, int> > m_map;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *watched, QEvent *event);
    ~LittleWidget();
    Ui::LittleWidget *ui;
private:
};

#endif // LITTLEWIDGET_H

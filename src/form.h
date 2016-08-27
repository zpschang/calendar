#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include "eventhandler.h"
#include "draglabel.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
signals:
    void close_signal();
public:
    EventHandler &handler;
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    explicit Form(EventHandler &_handler, QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~Form();
    Ui::Form *ui;
private:

};

#endif // FORM_H

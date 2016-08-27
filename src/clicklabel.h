#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>
class ClickLabel : public QLabel
{
    Q_OBJECT
signals:
    void left_clicked();
    void right_clicked();
public:
    ClickLabel(QString text, QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
};

#endif // CLICKLABEL_H

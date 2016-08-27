#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QMimeData>
#include <QList>
#include <QDrag>
class DragLabel : public QLabel
{
    Q_OBJECT
signals:
    void right_signal();
public:
    explicit DragLabel(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    QString file_path;
signals:

public slots:
};

#endif // DRAGWIDGET_H

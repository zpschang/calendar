#include "clicklabel.h"

ClickLabel::ClickLabel(QString text, QWidget *parent) : QLabel(text, parent)
{

}

void ClickLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        emit left_clicked();
    if(e->button() == Qt::RightButton)
        emit right_clicked();
}

#include "draglabel.h"

DragLabel::DragLabel(QWidget *parent) : QLabel(parent)
{

}

void DragLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        emit right_signal();
        return;
    }
    QMimeData *QD = new QMimeData;
    QList<QUrl> urls;
    urls.append(QUrl::fromLocalFile(file_path));
    QD->setUrls(urls);
    //QApplication::clipboard()->setMimeData(QD);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(QD);
    drag->start();
}

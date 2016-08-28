#ifndef DIALOGWIDGET_H
#define DIALOGWIDGET_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class DialogWidget;
}

class DialogWidget : public QDialog
{
    Q_OBJECT
signals:
    void del_0();
    void del_1();
    void del_2();
public:
    explicit DialogWidget(QWidget *parent = 0);
    ~DialogWidget();

private:
    Ui::DialogWidget *ui;
};

#endif // DIALOGWIDGET_H

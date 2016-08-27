#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "block.h"
#include "littlewidget.h"
#include "eventhandler.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(EventHandler &_handler, QWidget *parent = 0);
    EventHandler &handler;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout[8];
    QPushButton *btn_prev, *btn_next, *btn_fix;
    QLabel *txt_mid;
    QLabel *txt_date[7];
    Block *block[7][7];
    LittleWidget *little_widget;
    int year, month;
    static QString str_date[7];
    QPoint pointer;
    bool is_clicked, is_fixed;
    void update_month();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *, QEvent *);
    void slot(bool, Block *);
};

#endif // MAINWINDOW_H

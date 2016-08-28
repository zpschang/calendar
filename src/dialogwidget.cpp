#include "dialogwidget.h"
#include "ui_dialogwidget.h"

DialogWidget::DialogWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [this](){
        emit del_0();
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [this](){
        emit del_1();
    });
    connect(ui->pushButton_3, &QPushButton::clicked, [this](){
        emit del_2();
    });
}

DialogWidget::~DialogWidget()
{
    delete ui;
}

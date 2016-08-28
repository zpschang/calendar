#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=]{
        emit login(ui->lineEdit->text(), ui->lineEdit_2->text());
        close();
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=]{
        close();
    });
    connect(ui->pushButton_3, &QPushButton::clicked, [=]{
        emit regist(ui->lineEdit->text(), ui->lineEdit_2->text());
        close();
    });
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

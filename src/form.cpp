#include "form.h"
#include "ui_form.h"

Form::Form(EventHandler &_handler, QWidget *parent) :
    QWidget(parent),
    handler(_handler),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->textEdit->setAcceptDrops(false);
    setWindowTitle("添加事件");
    setAcceptDrops(true);
    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), [=](int index){
       if(index == 0)
       {
            ui->spinBox->setVisible(false);
            ui->spinBox_2->setVisible(false);
            ui->checkBox->setChecked(false);
            ui->checkBox->setVisible(false);
            ui->label_9->setVisible(false);
       }
       else
       {
           ui->spinBox->setVisible(true);
           ui->spinBox_2->setVisible(true);
           ui->checkBox->setVisible(true);
           ui->label_9->setVisible(true);
       }
       if(ui->checkBox->isChecked())
       {
           ui->spinBox->setVisible(false);
           ui->label_9->setVisible(false);
       }
    });
    connect(ui->checkBox, &QCheckBox::stateChanged, [=](int status){
        if(status)
        {
            ui->spinBox->setVisible(false);
            ui->label_9->setVisible(false);
        }
        else if(ui->comboBox->currentIndex() != 0)
        {
            ui->spinBox->setVisible(true);
            ui->label_9->setVisible(true);
        }
    });
    ui->comboBox->setCurrentIndex(1);
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        EventData *event = new EventData;
        event->start_date = ui->dateEdit->date();
        event->start_time = ui->timeEdit->time();
        event->end_time = ui->timeEdit_2->time();
        event->name = ui->lineEdit->text();
        event->description = ui->textEdit->toPlainText();
        event->repeat_style = (EventData::RepeatCycle)ui->comboBox->currentIndex();
        event->maxi_index = ui->spinBox->value();
        event->number = ui->spinBox_2->value();
        if(ui->checkBox->isChecked())
            event->maxi_index = -1;
        handler.events.push_back(event);
        close();
    });
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){
        close();
    });
}

void Form::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void Form::dropEvent(QDropEvent *e)
{
    QList<QUrl> url = e->mimeData()->urls();
    if(url.isEmpty())
        return;
    DragLabel *label = new DragLabel;
    connect(label, &DragLabel::right_signal, [=](){delete label;});
    label->setText(url.first().fileName());
    label->file_path = url.first().toLocalFile();
    ui->verticalLayout_4->addWidget(label);
    QFile::copy(url.first().toLocalFile(), url.first().fileName());
}

Form::~Form()
{
    delete ui;
}

void Form::closeEvent(QCloseEvent *)
{
    emit close_signal();
}

#include "form.h"
#include "ui_form.h"

Form::Form(EventHandler &_handler, QWidget *parent) :
    QWidget(parent),
    handler(_handler),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    event = 0;
    ui->textEdit->setAcceptDrops(false);
    setAcceptDrops(true);
    ui->label_10->setAutoFillBackground(true);
    setWindowTitle("添加事件");
    color = Qt::white;
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white);
    ui->label_10->setPalette(palette);
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
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        color = QColorDialog::getColor(Qt::white, this);
        qDebug() << color;
        QPalette palette;
        palette.setColor(QPalette::Background, color);
        ui->label_10->setPalette(palette);
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        for(int i = 0; i < (int)handler.events.size(); i++)
            if(handler.events[i] == this->event)
            {
                handler.events.erase(handler.events.begin() + i);
                break;
            }
        EventData *event = new EventData;
        write_to_event(event);
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
    connect(label, &DragLabel::right_signal, [=](){
        ui->verticalLayout_4->removeWidget(label);
        label->deleteLater();
        for(int i = 0; i < (int)file_paths.size(); i++)
            if(file_paths[i] == label->text())
            {
                file_paths.erase(file_paths.begin() + i);
                break;
            }
    });
    file_paths.push_back(url.first().fileName());
    label->setText(url.first().fileName());
    label->file_path = url.first().toLocalFile();
    ui->verticalLayout_4->addWidget(label);
    QFile::copy(url.first().toLocalFile(), url.first().fileName());
}

void Form::read_from_event(EventData *event)
{
    this->event = event;
    QPalette palette;
    palette.setColor(QPalette::Background, event->color);
    ui->label_10->setPalette(palette);
    ui->dateEdit->setDate(event->start_date);
    ui->timeEdit->setTime(event->start_time);
    ui->timeEdit_2->setTime(event->end_time);
    ui->lineEdit->setText(event->name);
    ui->textEdit->setText(event->description);
    ui->comboBox->setCurrentIndex(event->repeat_style);
    ui->spinBox->setValue(event->maxi_index);
    ui->spinBox_2->setValue(event->number);
    ui->pushButton_2->setText("完成");
    ui->pushButton_3->setVisible(false);
    for(QString file_path : event->file_path)
    {
        DragLabel *label = new DragLabel;
        connect(label, &DragLabel::right_signal, [=](){
            ui->verticalLayout_4->removeWidget(label);
            label->deleteLater();
            for(int i = 0; i < file_paths.size(); i++)
                if(file_paths[i] == label->text())
                {
                    file_paths.erase(file_paths.begin() + i);
                    break;
                }
        });
        label->setText(file_path);
        ui->verticalLayout_4->addWidget(label);
        file_paths.push_back(file_path);
    }
}

void Form::write_to_event(EventData *event)
{
    event->color = color;
    event->start_date = ui->dateEdit->date();
    event->start_time = ui->timeEdit->time();
    event->end_time = ui->timeEdit_2->time();
    event->name = ui->lineEdit->text();
    event->description = ui->textEdit->toPlainText();
    event->repeat_style = (EventData::RepeatCycle)ui->comboBox->currentIndex();
    event->maxi_index = ui->spinBox->value();
    event->number = ui->spinBox_2->value();
    for(QString str : file_paths)
    {
        event->file_path.push_back(str);
    }
    if(ui->checkBox->isChecked())
        event->maxi_index = -1;
}

Form::~Form()
{
    delete ui;
}

void Form::closeEvent(QCloseEvent *)
{
    emit close_signal();
}

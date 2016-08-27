#include "block.h"
#include "ui_block.h"

Block::Block(EventHandler &_handler, QWidget *parent) :
    QWidget(parent),
    handler(_handler),
    ui(new Ui::Block)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(110, 130, 255));
    palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
    ui->label_2->setAutoFillBackground(true);
    ui->label_2->setPalette(palette);
    ui->label_5->setAutoFillBackground(true);
    ui->label_5->setPalette(palette);
}

void Block::load()
{
    vector<EventData *> selected;
    for(EventData *event : handler.events)
        if(event->is_in(date) >= 0)
            selected.push_back(event);
    sort(selected.begin(), selected.end(), [](EventData* x, EventData *y){
        return x->start_time < y->start_time;
    });
    if(selected.size() >= 1)
    {
        ui->label_1->setText(" " + selected[0]->name);
        ui->label_4->setText(selected[0]->start_time.toString("hh:mm") + " ");
    }
    else
    {
        ui->label_1->setText("");
        ui->label_4->setText("");
    }
    if(selected.size() >= 2)
    {
        ui->label_2->setText(" " + selected[1]->name);
        ui->label_5->setText(selected[1]->start_time.toString("hh:mm") + " ");
    }
    else
    {
        ui->label_2->setText("");
        ui->label_5->setText("");
    }
    if(selected.size() >= 3)
    {
        ui->label_3->setText(" " + selected[2]->name);
        ui->label_6->setText(selected[2]->start_time.toString("hh:mm") + " ");
    }
    else
    {
        ui->label_3->setText("");
        ui->label_6->setText("");
    }
}

Block::~Block()
{
    delete ui;
}

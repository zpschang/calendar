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
    ui->label_1->setAutoFillBackground(true);
    ui->label_2->setAutoFillBackground(true);
    ui->label_3->setAutoFillBackground(true);
    ui->label_4->setAutoFillBackground(true);
    ui->label_5->setAutoFillBackground(true);
    ui->label_6->setAutoFillBackground(true);
}

void Block::load(bool is_fixed)
{
    vector<EventData *> selected;
    for(EventData *event : handler.events)
        if(event->is_in(date) >= 0)
            selected.push_back(event);
    sort(selected.begin(), selected.end(), [](EventData* x, EventData *y){
        return x->start_time < y->start_time;
    });
    QPalette palette;
    if(selected.size() >= 1)
    {
        ui->label_1->setText(" " + selected[0]->name);
        ui->label_4->setText(selected[0]->start_time.toString("hh:mm") + " ");
        palette.setColor(QPalette::Background, selected[0]->color);
    }
    else
    {
        ui->label_1->setText("");
        ui->label_4->setText("");
        palette.setColor(QPalette::Background, QColor(255, 255, 255, 0));
    }
    ui->label_1->setPalette(palette);
    ui->label_4->setPalette(palette);
    if(selected.size() >= 2)
    {
        ui->label_2->setText(" " + selected[1]->name);
        ui->label_5->setText(selected[1]->start_time.toString("hh:mm") + " ");
        palette.setColor(QPalette::Background, selected[1]->color);
    }
    else
    {
        ui->label_2->setText("");
        ui->label_5->setText("");
        palette.setColor(QPalette::Background, QColor(255, 255, 255, 0));
    }
    ui->label_2->setPalette(palette);
    ui->label_5->setPalette(palette);
    if(selected.size() >= 3)
    {
        ui->label_3->setText(" " + selected[2]->name);
        ui->label_6->setText(selected[2]->start_time.toString("hh:mm") + " ");
        palette.setColor(QPalette::Background, selected[2]->color);
    }
    else
    {
        ui->label_3->setText("");
        ui->label_6->setText("");
        palette.setColor(QPalette::Background, QColor(255, 255, 255, 0));
    }
    ui->label_3->setPalette(palette);
    ui->label_6->setPalette(palette);
    //palette.setColor(QPalette::Background, QColor(255, 255, 255, is_fixed ? 0 : 255));
    //setPalette(palette);
    //if(data == )
}

Block::~Block()
{
    delete ui;
}

#include "littlewidget.h"
#include "ui_littlewidget.h"
#include "ui_form.h"
#include <QDebug>
#include <QHBoxLayout>

LittleWidget::LittleWidget(EventHandler &_handler, QDate _date, QWidget *parent) :
    QWidget(parent),
    handler(_handler),
    date(_date),
    ui(new Ui::LittleWidget)
{
    ui->setupUi(this);
    menu_window = 0;
    form = 0;
    dialog = 0;
    setWindowOpacity(0.9);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 255, 255, 255));
    setPalette(palette);
    setWindowFlags(Qt::FramelessWindowHint);
    QFont ft;
    ft.setPointSize(32);
    label = new QLabel(this);
    label->setMargin(6);
    label->setFont(ft);
    label->setText(" " + QString::number(date.year()) + tr("年") + QString::number(date.month()) + tr("月") + QString::number(date.day()) + tr("日"));
    QPoint last = label->geometry().bottomLeft() + QPoint(0, 40);
    vector<EventData *> selected;
    for(EventData *event : handler.events)
        if(event->is_in(date) >= 0)
            selected.push_back(event);
    sort(selected.begin(), selected.end(), [](EventData *x, EventData *y){
        return x->start_time < y->start_time;
    });

    for(EventData *event : selected)
    {
        int index = event->is_in(date);
        if(index >= 0)
        {
            QPalette palette;
            palette.setColor(QPalette::Background, event->color);
            ft.setPointSize(32);
            QWidget *widget = new QWidget(this);
            m_map[widget] = make_pair(event, index);
            widget->installEventFilter(this);
            widget->setGeometry(QRect(last, QSize(width(), 50)));
            QHBoxLayout *h_layout = new QHBoxLayout(widget);
            h_layout->layout()->setContentsMargins(15, 0, 5, 0);
            h_layout->setSpacing(0);
            QLabel *label_event = new QLabel;
            label_event->setFont(ft);
            label_event->setMargin(6);
            label_event->setText(event->name);
            label_event->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            label_event->setAutoFillBackground(true);
            label_event->setPalette(palette);
            h_layout->addWidget(label_event);

            QLabel *label_time = new QLabel;
            ft.setPixelSize(20);
            label_time->setFont(ft);
            label_time->setMargin(6);
            label_time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            label_time->setText(event->start_time.toString("HH:mm") + " - " + event->end_time.toString("HH:mm"));
            h_layout->addWidget(label_time);
            label_time->setAutoFillBackground(true);
            label_time->setPalette(palette);
            last = widget->geometry().bottomLeft();
        }
    }
    btn = new QPushButton(this);
    btn->move(width()-100, last.y()+20);
    btn->setText(tr("返回"));
    btn_add = new QPushButton(this);
    btn_add->move(30, last.y()+20);
    btn_add->setText(tr("添加"));
    resize(width(), last.y()+60);
    connect(btn, &QPushButton::clicked, [=](){
        emit close_signal(false);
        delete this;
    });
    connect(btn_add, &QPushButton::clicked, [=](){
        if(this->form)
        {
            delete this->form;
            this->form = 0;
        }
        Form *form = new Form(handler);
        this->form = form;
        form->show();
        form->ui->dateEdit->setDate(date);
        connect(form, &Form::close_signal, [=](){
            emit close_signal(true);
            delete this;
        });
    });
    is_clicked = false;
}

void LittleWidget::mousePressEvent(QMouseEvent *e)
{
    is_clicked = true;
    pointer = e->globalPos();
}

void LittleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(is_clicked)
    {
        move(pos() + e->globalPos() - pointer);
        pointer = e->globalPos();
    }
}

void LittleWidget::mouseReleaseEvent(QMouseEvent *)
{
    is_clicked = false;
}

bool LittleWidget::eventFilter(QObject *watched, QEvent *event)
{
    QWidget *widget = (QWidget*)watched;
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouse_event = (QMouseEvent*)event;
        if(mouse_event->button() == Qt::LeftButton)
        {

            return true;
        }
        if(mouse_event->button() == Qt::RightButton)
        {
            QWidget *new_window = new QWidget;
            if(menu_window)
                delete menu_window;
            menu_window = new_window;
            menu_window->installEventFilter(this);
            new_window->setWindowFlags(Qt::FramelessWindowHint);
            new_window->setContextMenuPolicy(Qt::ActionsContextMenu);
            QPalette palette;
            palette.setColor(QPalette::Background, Qt::white);
            new_window->setPalette(palette);
            new_window->setWindowOpacity(0.9);
            qDebug() << m_map[widget].first << m_map[widget].second;

            ClickLabel *edit, *del;
            QVBoxLayout *v_layout = new QVBoxLayout(new_window);
            edit = new ClickLabel(tr("编辑事件"));
            del = new ClickLabel(tr("删除事件"));
            v_layout->addWidget(edit);
            v_layout->addWidget(del);

            new_window->move(mouse_event->globalPos());
            new_window->show();
            EventData *event = m_map[widget].first;
            int index = m_map[widget].second;

            connect(edit, &ClickLabel::left_clicked, [=](){
                if(this->form)
                {
                    delete this->form;
                    this->form = 0;
                }
                Form *form = new Form(handler);
                this->form = form;
                form->read_from_event(event);
                form->setWindowTitle(tr("编辑事件"));
                form->show();

                connect(form, &Form::close_signal, [=](){
                    emit close_signal(true);
                    delete this;
                });
            });

            connect(del, &ClickLabel::left_clicked, [=](){
                if(this->dialog)
                {
                    delete this->dialog;
                    this->dialog = 0;
                }
                DialogWidget *dialog = new DialogWidget;
                this->dialog = dialog;
                //dialog->setWindowFlags(Qt::FramelessWindowHint);
                //dialog->setWindowOpacity(0.9);
                dialog->show();
                connect(dialog, &DialogWidget::del_0, [=](){
                    event->del_day(index);
                    emit close_signal(true);
                    delete this;
                });
                connect(dialog, &DialogWidget::del_1, [=](){
                    event->del_day_after(index);
                    emit close_signal(true);
                    delete this;
                });
                connect(dialog, &DialogWidget::del_2, [=](){
                    for(int i = 0; i < (int)handler.events.size(); i++)
                        if(handler.events[i] == event)
                        {
                            handler.events.erase(handler.events.begin() + i);
                            break;
                        }
                    emit close_signal(true);
                    delete this;
                });
            });
            return true;
        }
    }
    if(event->type() == QEvent::MouseButtonDblClick)
    {

        return true;
    }
    if(event->type() == QEvent::WindowDeactivate && widget == menu_window)
    {
        qDebug() << "aaa";
        menu_window->close();
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

void LittleWidget::closeEvent(QCloseEvent *)
{

}

LittleWidget::~LittleWidget()
{
    if(form)
        delete form;
    if(menu_window)
        delete menu_window;
    if(dialog)
        delete dialog;
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_block.h"
QString MainWindow::str_date[7] = {"周日", "周一", "周二", "周三", "周四", "周五", "周六"};

MainWindow::MainWindow(EventHandler &_handler, QWidget *parent) :
    QMainWindow(parent),
    handler(_handler),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    QMenuBar *menubar = new QMenuBar(this);
    QMenu *menu = new QMenu("menu");
    QAction *act_1 = menu->addAction("login");
    menubar->addMenu(menu);
    */
    v_layout = new QVBoxLayout;
    ui->centralWidget->setLayout(v_layout);
    v_layout->setSpacing(1);
    little_widget = 0;
    int i, j;
    for(i = 0; i < 8; i++)
    {
        h_layout[i] = new QHBoxLayout;
        h_layout[i]->setSpacing(1);
        v_layout->addLayout(h_layout[i], (i == 0) ? 1 : 2);
        if(i > 0)
        {
            /*QFrame *line = new QFrame;
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            v_layout->addWidget(line);*/
        }
    }

    btn_prev = new QPushButton("<");
    btn_next = new QPushButton(">");
    is_fixed = false;
    btn_fix = new QPushButton("+");
    connect(btn_fix, &QPushButton::clicked, [this]{
        is_fixed = !is_fixed;
        QPalette palette;
        palette.setColor(QPalette::WindowText, is_fixed ? Qt::white : Qt::black);

        int i, j;
        for(i = 0; i < 6; i++)
            for(j = 0; j < 7; j++)
            {
                block[i][j]->ui->label_1->setPalette(palette);
                //block[i][j]->ui->label_2->setPalette(palette);
                block[i][j]->ui->label_3->setPalette(palette);
                block[i][j]->ui->label_4->setPalette(palette);
                //block[i][j]->ui->label_5->setPalette(palette);
                block[i][j]->ui->label_6->setPalette(palette);
            }
        palette.setColor(QPalette::Background, QColor(255, 255, 255, is_fixed ? 0 : 255));
        setPalette(palette);
        for(i = 0; i < 6; i++)
            for(j = 0; j < 7; j++)
                if(block[i][j]->date.month() == month)
                    block[i][j]->ui->txt->setPalette(palette);
        palette.setColor(QPalette::Background, Qt::white);

        for(i = 0; i < 7; i++)
            txt_date[i]->setPalette(palette);
        txt_mid->setPalette(palette);
        btn_fix->setText(is_fixed ? "-" : "+");
    });
    connect(btn_prev, &QPushButton::clicked, [this]{
        month--;
        if(month == 0)
            month = 12, year--;
        update_month();
    });
    connect(btn_next, &QPushButton::clicked, [this]{
        month++;
        if(month == 13)
            month = 1, year++;
        update_month();
    });

    txt_mid = new QLabel;
    txt_mid->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(20);
    txt_mid->setFont(ft);
    h_layout[0]->addWidget(btn_prev, 1);
    h_layout[0]->addWidget(txt_mid, 7);
    h_layout[0]->addWidget(btn_fix, 1);
    h_layout[0]->addWidget(btn_next, 1);
    QDate current = QDateTime::currentDateTime().date();
    year = current.year(), month = current.month();
    ft.setPointSize(16);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    txt_mid->setPalette(palette);
    for(i = 0; i < 7; i++)
    {
        txt_date[i] = new QLabel(str_date[i]);
        txt_date[i]->installEventFilter(this);
        txt_date[i]->setAlignment(Qt::AlignCenter);
        txt_date[i]->setMargin(0);
        txt_date[i]->setFont(ft);
        txt_date[i]->setPalette(palette);
        h_layout[1]->addWidget(txt_date[i]);

        /*QFrame *line = new QFrame;
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        h_layout[1]->addWidget(line);*/
    }
    for(i = 0; i < 6; i++)
        for(j = 0; j < 7; j++)
        {
            block[i][j] = new Block(handler, this);
            block[i][j]->installEventFilter(this);
            block[i][j]->ui->txt->setAlignment(Qt::AlignLeft);
            block[i][j]->ui->txt->setMargin(5);
            block[i][j]->setFont(ft);
            h_layout[i+2]->addWidget(block[i][j]);
            /*QFrame *line = new QFrame;
            line->setFrameShape(QFrame::VLine);
            line->setFrameShadow(QFrame::Sunken);
            h_layout[i+2]->addWidget(line);*/
        }
    update_month();
}

void MainWindow::update_month()
{
    QDate now, current = QDateTime::currentDateTime().date();
    txt_mid->setText(QString::number(year) + QString("年") + QString::number(month) + QString("月"));
    now.setDate(year, month, 1);
    while(now.dayOfWeek() != 7)
        now = now.addDays(-1);
    int i, j;
    for(i = 0; i < 6; i++)
    {
        for(j = 0; j < 7; j++)
        {
            QPalette palette = block[i][j]->palette();
            if(j == 0 || j == 6)
                palette.setColor(QPalette::Background, QColor(200, 222, 255, 0));
            else
                palette.setColor(QPalette::Background, QColor(255, 255, 255, 0));
            block[i][j]->setPalette(palette);
        }
    }
    for(i = 0; i < 6; i++)
        for(j = 0; j < 7; j++)
        {
            block[i][j]->ui->txt->setText(QString::number(now.day()));
            block[i][j]->date = now;
            block[i][j]->load();
            QPalette palette;
            if(now.month() != month)
                palette.setColor(QPalette::WindowText, Qt::gray);
            else
                palette.setColor(QPalette::WindowText, is_fixed ? Qt::white : Qt::black);
            block[i][j]->ui->txt->setPalette(palette);

            if(now == current)
            {
                palette.setColor(QPalette::Background, QColor(160, 255, 160, 150));
                block[i][j]->setPalette(palette);
            }
            now = now.addDays(1);
        }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(0, 255, 0, 255)));
    QPixmap pixmap("/Users/pushi/Documents/1.png");
    //painter.drawPixmap(100, 100, pixmap);
    int i, j;
    painter.setPen(QColor(222, 222, 222, 150));
    for(i = 0; i < 7; i++)
    {
        QRect rect = txt_date[i]->geometry();
        painter.drawLine(rect.topRight() + QPointF(1.5, 0), rect.bottomRight() + QPointF(1.5, 1.5));
        painter.drawLine(rect.bottomLeft() + QPointF(0, 1.5), rect.bottomRight() + QPointF(1.5, 1.5));
    }
    for(i = 0; i < 6; i++)
        for(j = 0; j < 7; j++)
        {
            QRect rect = block[i][j]->geometry();
            painter.drawLine(rect.topRight() + QPointF(1.5, 0), rect.bottomRight() + QPointF(1.5, 1.5));
            painter.drawLine(rect.bottomLeft() + QPointF(0, 1.5), rect.bottomRight() + QPointF(1.5, 1.5));
        }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    pointer = e->globalPos();
    is_clicked = true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(is_clicked)
    {
        move(pos() + e->globalPos() - pointer);
        pointer = e->globalPos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    is_clicked = false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    //e->ignore();
}

void MainWindow::slot(bool is_create, Block *block)
{
    if(is_create)
    {
        for(int i = 0; i < 6; i++)
            for(int j = 0; j < 7; j++)
                this->block[i][j]->load();
        QPoint pos = little_widget->pos();
        little_widget = new LittleWidget(handler, block->date);
        little_widget->move(pos);
        little_widget->show();
        connect(little_widget, &LittleWidget::close_signal, [=](bool t){
            slot(t, block);
        });
    }
    else
        little_widget = 0;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        if(little_widget)
        {
            delete little_widget;
            little_widget = 0;
        }
        Block *block = (Block*)obj;
        for(int i = 0; i < 7; i++)
            if((QLabel*)txt_date[i] == (QLabel*)obj)
            {
                return true; // to be modified
            }

        LittleWidget *w = new LittleWidget(handler, block->date);
        little_widget = w;
        connect(little_widget, &LittleWidget::close_signal, [=](bool is_create){
            slot(is_create, block);
        });
        QMouseEvent *mouse_event = (QMouseEvent*)e;
        QPoint pt = mouse_event->globalPos();
        pt.setY(std::min(pt.y(), QApplication::desktop()->screenGeometry().height() - 200));
        w->move(pt);
        w->show();
        return true;
    }
    if(e->type() == QEvent::MouseMove)
        return true;
    return QMainWindow::eventFilter(obj, e);
}

MainWindow::~MainWindow()
{
    delete ui;
}

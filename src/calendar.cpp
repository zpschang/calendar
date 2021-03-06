#include "calendar.h"
#include "ui_calendar.h"
#include "ui_block.h"
QString Calendar::str_date[7] = {};

Calendar::Calendar(EventHandler &_handler, LoginHandler &_login_handler, bool _is_fixed, QWidget *parent) :
    QMainWindow(parent),
    handler(_handler),
    login_handler(_login_handler),
    is_fixed(_is_fixed),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);
    str_date[0] = tr("周日");
    str_date[1] = tr("周一");
    str_date[2] = tr("周二");
    str_date[3] = tr("周三");
    str_date[4] = tr("周四");
    str_date[5] = tr("周五");
    str_date[6] = tr("周六");

    v_layout = new QVBoxLayout;
    ui->centralWidget->setLayout(v_layout);
    v_layout->setSpacing(1);
    little_widget = 0;
    login_widget = 0;


    int i, j;
    for(i = 0; i < 8; i++)
    {
        h_layout[i] = new QHBoxLayout;
        h_layout[i]->setSpacing(1);
        v_layout->addLayout(h_layout[i], (i == 0) ? 1 : 2);
    }

    btn_prev = new QPushButton("<");
    btn_next = new QPushButton(">");

    QPalette palette0;
    palette0.setColor(QPalette::Background, QColor(255, 255, 255, is_fixed ? 0 : 255));
    setPalette(palette0);
    setWindowFlags(Qt::FramelessWindowHint);
    if(is_fixed)
        setWindowFlags(windowFlags() | Qt::WindowTransparentForInput);
    else
        setWindowFlags(windowFlags() & ~Qt::WindowTransparentForInput);

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
    txt_user = new QLabel(tr("用户：") + "\"\"");
    txt_user->setAlignment(Qt::AlignCenter);
    txt_mid = new QLabel;
    txt_mid->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(20);
    txt_mid->setFont(ft);
    h_layout[0]->addWidget(btn_prev, 1);
    h_layout[0]->addWidget(txt_mid, 7);
    h_layout[0]->addWidget(txt_user, 1);
    //h_layout[0]->addWidget(btn_fix, 1);
    h_layout[0]->addWidget(btn_next, 1);
    QDate current = QDateTime::currentDateTime().date();
    year = current.year(), month = current.month();
    ft.setPointSize(16);
    QPalette palette;
    palette.setColor(QPalette::WindowText, is_fixed ? Qt::white : Qt::black);
    txt_mid->setPalette(palette);
    txt_user->setFont(ft);
    txt_user->setPalette(palette);
    for(i = 0; i < 7; i++)
    {
        txt_date[i] = new QLabel(str_date[i]);
        txt_date[i]->installEventFilter(this);
        txt_date[i]->setAlignment(Qt::AlignCenter);
        txt_date[i]->setMargin(0);
        txt_date[i]->setFont(ft);
        txt_date[i]->setPalette(palette);
        h_layout[1]->addWidget(txt_date[i]);
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
        }
    update_month();
    show();
    QMenuBar *menubar = new QMenuBar(this);
    QMenu *menu = new QMenu("菜单");
    menubar->addMenu(menu);
    QAction *action = menu->addAction(is_fixed ? "解除固定" : "固定");
    connect(action, &QAction::triggered, [=]{
        Calendar *new_calendar = new Calendar(handler, login_handler, !is_fixed);
        new_calendar->show();
        new_calendar->move(pos());
        deleteLater();
    });
}

void Calendar::update_month()
{
    QDate now, current = QDateTime::currentDateTime().date();
    txt_mid->setText(QString::number(year) + tr("年") + QString::number(month) + tr("月"));
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
            block[i][j]->load(is_fixed);
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

void Calendar::paintEvent(QPaintEvent *)
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

void Calendar::mousePressEvent(QMouseEvent *e)
{
    pointer = e->globalPos();
    is_clicked = true;
}

void Calendar::mouseMoveEvent(QMouseEvent *e)
{
    if(is_clicked && !is_fixed)
    {
        move(pos() + e->globalPos() - pointer);
        pointer = e->globalPos();
    }
}

void Calendar::mouseReleaseEvent(QMouseEvent *)
{
    is_clicked = false;
}

void Calendar::closeEvent(QCloseEvent *)
{
    //e->ignore();
}

void Calendar::slot(bool is_create, Block *block)
{
    if(is_create)
    {
        for(int i = 0; i < 6; i++)
            for(int j = 0; j < 7; j++)
                this->block[i][j]->load(is_fixed);
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

void Calendar::contextMenuEvent(QContextMenuEvent *)
{
    QMenu *menu = new QMenu(this);
    QAction *action_login, *action_import, *action_export, *action_merge;
    action_login = new QAction(tr("登录"), this);
    action_import = new QAction(tr("导入"), this);
    action_export = new QAction(tr("导出"), this);
    action_merge = new QAction(tr("合并"), this);
    menu->addAction(action_login);
    menu->addAction(action_import);
    menu->addAction(action_export);
    menu->addAction(action_merge);
    connect(action_login, &QAction::triggered, [=]{
        if(this->login_widget)
        {
            delete this->login_widget;
            this->login_widget = 0;
        }
        LoginWidget *login_widget = new LoginWidget;
        login_widget->show();
        this->login_widget = login_widget;
        connect(login_widget, &LoginWidget::login, [=](QString user, QString password){
            QString info = login_handler.login(user, password);
            if(info == "success")
            {
                handler.user = user;
                handler.password = password;
                txt_user->setText(tr("用户：") + "\"" + user + "\"");
                handler.events.clear();
                for(int i = 0; i < 6; i++)
                    for(int j = 0; j < 7; j++)
                        block[i][j]->load(is_fixed);
            }
            qDebug() << info;
        });
        connect(login_widget, &LoginWidget::regist, [=](QString user, QString password){
            QString info = login_handler.regist(user, password);
            if(info == "success")
            {
                handler.user = user;
                handler.password = password;
                txt_user->setText(tr("用户") + "\"" + user + "\"");
                handler.events.clear();
                for(int i = 0; i < 6; i++)
                    for(int j = 0; j < 7; j++)
                        block[i][j]->load(is_fixed);
            }
            qDebug() << info;
        });
    });
    connect(action_import, &QAction::triggered, [=]{
        QUrl url = QFileDialog::getOpenFileUrl(this);
        QString info = handler.read_data(url.path());
        qDebug() << info;
        if(info == "success")
        {
            for(int i = 0; i < 6; i++)
                for(int j = 0; j < 7; j++)
                    block[i][j]->load(is_fixed);
        }
    });
    connect(action_export, &QAction::triggered, [=]{
        QUrl url = QFileDialog::getSaveFileUrl(this);
        handler.write_data(url.path());
    });
    connect(action_merge, &QAction::triggered, [=]{
        QUrl url = QFileDialog::getOpenFileUrl(this);
        EventHandler _handler;
        _handler.user = handler.user;
        _handler.password = handler.password;
        QString info = _handler.read_data(url.path());
        qDebug() << info;
        if(info == "success")
        {
            handler.merge(_handler);
            for(int i = 0; i < 6; i++)
                for(int j = 0; j < 7; j++)
                    block[i][j]->load(is_fixed);
        }
    });
    menu->exec(cursor().pos());

}

bool Calendar::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress && ((QMouseEvent *)e)->button() == Qt::LeftButton)
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

Calendar::~Calendar()
{
    delete login_widget;
    delete little_widget;
    delete ui;
}

#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QVBoxLayout>
#include <algorithm>
#include "eventhandler.h"

namespace Ui {
class Block;
}

class Block : public QWidget
{
    Q_OBJECT

public:
    explicit Block(EventHandler &_handler, QWidget *parent = 0);
    EventHandler &handler;
    QDate date;
    void load();
    ~Block();
    Ui::Block *ui;
private:

};

#endif // BLOCK_H

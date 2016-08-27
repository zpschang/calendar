/********************************************************************************
** Form generated from reading UI file 'block.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLOCK_H
#define UI_BLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Block
{
public:
    QVBoxLayout *verticalLayout_3;
    QLabel *txt;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_1;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_1;
    QLabel *label_3;
    QLabel *label_6;

    void setupUi(QWidget *Block)
    {
        if (Block->objectName().isEmpty())
            Block->setObjectName(QStringLiteral("Block"));
        Block->resize(162, 161);
        verticalLayout_3 = new QVBoxLayout(Block);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        txt = new QLabel(Block);
        txt->setObjectName(QStringLiteral("txt"));

        verticalLayout_3->addWidget(txt);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_1 = new QLabel(Block);
        label_1->setObjectName(QStringLiteral("label_1"));
        QFont font;
        font.setPointSize(11);
        label_1->setFont(font);

        horizontalLayout_9->addWidget(label_1);

        label_4 = new QLabel(Block);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_4);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(Block);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_8->addWidget(label_2);

        label_5 = new QLabel(Block);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_5);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        label_3 = new QLabel(Block);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_1->addWidget(label_3);

        label_6 = new QLabel(Block);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_1->addWidget(label_6);


        verticalLayout_3->addLayout(horizontalLayout_1);

        verticalLayout_3->setStretch(0, 2);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(2, 1);
        verticalLayout_3->setStretch(3, 1);

        retranslateUi(Block);

        QMetaObject::connectSlotsByName(Block);
    } // setupUi

    void retranslateUi(QWidget *Block)
    {
        Block->setWindowTitle(QApplication::translate("Block", "Form", 0));
        txt->setText(QApplication::translate("Block", "TextLabel", 0));
        label_1->setText(QString());
        label_4->setText(QString());
        label_2->setText(QString());
        label_5->setText(QString());
        label_3->setText(QString());
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Block: public Ui_Block {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLOCK_H

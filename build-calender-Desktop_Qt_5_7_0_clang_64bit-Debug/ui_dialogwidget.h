/********************************************************************************
** Form generated from reading UI file 'dialogwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWIDGET_H
#define UI_DIALOGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *DialogWidget)
    {
        if (DialogWidget->objectName().isEmpty())
            DialogWidget->setObjectName(QStringLiteral("DialogWidget"));
        DialogWidget->resize(247, 228);
        horizontalLayout_2 = new QHBoxLayout(DialogWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(DialogWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(DialogWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(DialogWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(DialogWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogWidget);

        QMetaObject::connectSlotsByName(DialogWidget);
    } // setupUi

    void retranslateUi(QWidget *DialogWidget)
    {
        DialogWidget->setWindowTitle(QApplication::translate("DialogWidget", "Form", 0));
        label->setText(QApplication::translate("DialogWidget", "\345\210\240\351\231\244\346\226\271\345\274\217\357\274\237", 0));
        pushButton->setText(QApplication::translate("DialogWidget", "\345\210\240\351\231\244\345\275\223\345\244\251\344\272\213\344\273\266", 0));
        pushButton_2->setText(QApplication::translate("DialogWidget", "\345\210\240\351\231\244\344\273\245\345\220\216\344\272\213\344\273\266", 0));
        pushButton_3->setText(QApplication::translate("DialogWidget", "\345\210\240\351\231\244\344\272\213\344\273\266\345\272\217\345\210\227", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogWidget: public Ui_DialogWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWIDGET_H

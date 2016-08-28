/********************************************************************************
** Form generated from reading UI file 'calendar.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDAR_H
#define UI_CALENDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calendar
{
public:
    QAction *action123;
    QAction *actionAaa;
    QWidget *centralWidget;

    void setupUi(QMainWindow *Calendar)
    {
        if (Calendar->objectName().isEmpty())
            Calendar->setObjectName(QStringLiteral("Calendar"));
        Calendar->resize(1018, 688);
        action123 = new QAction(Calendar);
        action123->setObjectName(QStringLiteral("action123"));
        actionAaa = new QAction(Calendar);
        actionAaa->setObjectName(QStringLiteral("actionAaa"));
        centralWidget = new QWidget(Calendar);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Calendar->setCentralWidget(centralWidget);

        retranslateUi(Calendar);

        QMetaObject::connectSlotsByName(Calendar);
    } // setupUi

    void retranslateUi(QMainWindow *Calendar)
    {
        Calendar->setWindowTitle(QApplication::translate("Calendar", "MainWindow", 0));
        action123->setText(QApplication::translate("Calendar", "123", 0));
        actionAaa->setText(QApplication::translate("Calendar", "aaa", 0));
    } // retranslateUi

};

namespace Ui {
    class Calendar: public Ui_Calendar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDAR_H

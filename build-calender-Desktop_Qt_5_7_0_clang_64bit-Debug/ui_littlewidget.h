/********************************************************************************
** Form generated from reading UI file 'littlewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LITTLEWIDGET_H
#define UI_LITTLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LittleWidget
{
public:

    void setupUi(QWidget *LittleWidget)
    {
        if (LittleWidget->objectName().isEmpty())
            LittleWidget->setObjectName(QStringLiteral("LittleWidget"));
        LittleWidget->resize(301, 400);

        retranslateUi(LittleWidget);

        QMetaObject::connectSlotsByName(LittleWidget);
    } // setupUi

    void retranslateUi(QWidget *LittleWidget)
    {
        LittleWidget->setWindowTitle(QApplication::translate("LittleWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class LittleWidget: public Ui_LittleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LITTLEWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'fawrekeditorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAWREKEDITORWIDGET_H
#define UI_FAWREKEDITORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FawrekEditorClass
{
public:

    void setupUi(QWidget *FawrekEditorClass)
    {
        if (FawrekEditorClass->objectName().isEmpty())
            FawrekEditorClass->setObjectName(QStringLiteral("FawrekEditorClass"));
        FawrekEditorClass->resize(600, 400);

        retranslateUi(FawrekEditorClass);

        QMetaObject::connectSlotsByName(FawrekEditorClass);
    } // setupUi

    void retranslateUi(QWidget *FawrekEditorClass)
    {
        FawrekEditorClass->setWindowTitle(QApplication::translate("FawrekEditorClass", "FawrekEditor", 0));
    } // retranslateUi

};

namespace Ui {
    class FawrekEditorClass: public Ui_FawrekEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAWREKEDITORWIDGET_H

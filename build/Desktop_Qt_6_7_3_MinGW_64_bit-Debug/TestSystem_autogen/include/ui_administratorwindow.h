/********************************************************************************
** Form generated from reading UI file 'administratorwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINISTRATORWINDOW_H
#define UI_ADMINISTRATORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdministratorWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdministratorWindow)
    {
        if (AdministratorWindow->objectName().isEmpty())
            AdministratorWindow->setObjectName("AdministratorWindow");
        AdministratorWindow->resize(800, 600);
        centralwidget = new QWidget(AdministratorWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(300, 160, 208, 191));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        AdministratorWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AdministratorWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        AdministratorWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AdministratorWindow);
        statusbar->setObjectName("statusbar");
        AdministratorWindow->setStatusBar(statusbar);

        retranslateUi(AdministratorWindow);

        QMetaObject::connectSlotsByName(AdministratorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdministratorWindow)
    {
        AdministratorWindow->setWindowTitle(QCoreApplication::translate("AdministratorWindow", "\347\256\241\347\220\206\345\221\230\345\212\237\350\203\275", nullptr));
        label->setText(QCoreApplication::translate("AdministratorWindow", "\351\242\230\345\272\223\347\256\241\347\220\206\347\263\273\347\273\237-\347\256\241\347\220\206\345\221\230\347\211\210\346\234\254", nullptr));
        pushButton->setText(QCoreApplication::translate("AdministratorWindow", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AdministratorWindow", "\347\273\204\345\215\267\345\212\237\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdministratorWindow: public Ui_AdministratorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINISTRATORWINDOW_H

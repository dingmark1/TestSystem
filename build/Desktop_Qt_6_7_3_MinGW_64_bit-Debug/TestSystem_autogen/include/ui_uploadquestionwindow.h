/********************************************************************************
** Form generated from reading UI file 'uploadquestionwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADQUESTIONWINDOW_H
#define UI_UPLOADQUESTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UploadQuestionWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *singleselect_pushButton;
    QPushButton *mulselect_pushButton_2;
    QPushButton *judge_pushButton_3;
    QPushButton *short_pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UploadQuestionWindow)
    {
        if (UploadQuestionWindow->objectName().isEmpty())
            UploadQuestionWindow->setObjectName("UploadQuestionWindow");
        UploadQuestionWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UploadQuestionWindow->sizePolicy().hasHeightForWidth());
        UploadQuestionWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(UploadQuestionWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(220, 150, 351, 211));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        singleselect_pushButton = new QPushButton(layoutWidget);
        singleselect_pushButton->setObjectName("singleselect_pushButton");

        gridLayout->addWidget(singleselect_pushButton, 0, 0, 1, 1);

        mulselect_pushButton_2 = new QPushButton(layoutWidget);
        mulselect_pushButton_2->setObjectName("mulselect_pushButton_2");
        mulselect_pushButton_2->setBaseSize(QSize(0, 0));
        mulselect_pushButton_2->setCursor(QCursor(Qt::CursorShape::ArrowCursor));

        gridLayout->addWidget(mulselect_pushButton_2, 0, 1, 1, 1);

        judge_pushButton_3 = new QPushButton(layoutWidget);
        judge_pushButton_3->setObjectName("judge_pushButton_3");

        gridLayout->addWidget(judge_pushButton_3, 1, 0, 1, 1);

        short_pushButton_4 = new QPushButton(layoutWidget);
        short_pushButton_4->setObjectName("short_pushButton_4");

        gridLayout->addWidget(short_pushButton_4, 1, 1, 1, 1);

        UploadQuestionWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UploadQuestionWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        UploadQuestionWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UploadQuestionWindow);
        statusbar->setObjectName("statusbar");
        UploadQuestionWindow->setStatusBar(statusbar);

        retranslateUi(UploadQuestionWindow);

        QMetaObject::connectSlotsByName(UploadQuestionWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UploadQuestionWindow)
    {
        UploadQuestionWindow->setWindowTitle(QCoreApplication::translate("UploadQuestionWindow", "MainWindow", nullptr));
        singleselect_pushButton->setText(QCoreApplication::translate("UploadQuestionWindow", "\345\215\225\351\200\211\351\242\230", nullptr));
        mulselect_pushButton_2->setText(QCoreApplication::translate("UploadQuestionWindow", "\345\244\232\351\200\211\351\242\230", nullptr));
        judge_pushButton_3->setText(QCoreApplication::translate("UploadQuestionWindow", "\345\210\244\346\226\255\351\242\230", nullptr));
        short_pushButton_4->setText(QCoreApplication::translate("UploadQuestionWindow", "\347\256\200\347\255\224\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UploadQuestionWindow: public Ui_UploadQuestionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADQUESTIONWINDOW_H

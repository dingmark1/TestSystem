/********************************************************************************
** Form generated from reading UI file 'shortanswerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHORTANSWERWINDOW_H
#define UI_SHORTANSWERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShortAnswerWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QTextEdit *question_textEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QTextEdit *answer_textEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *subject_lineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *upload_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ShortAnswerWindow)
    {
        if (ShortAnswerWindow->objectName().isEmpty())
            ShortAnswerWindow->setObjectName("ShortAnswerWindow");
        ShortAnswerWindow->resize(800, 600);
        centralwidget = new QWidget(ShortAnswerWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_7);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_7->addWidget(label);

        question_textEdit = new QTextEdit(centralwidget);
        question_textEdit->setObjectName("question_textEdit");

        horizontalLayout_7->addWidget(question_textEdit);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        answer_textEdit = new QTextEdit(centralwidget);
        answer_textEdit->setObjectName("answer_textEdit");

        horizontalLayout->addWidget(answer_textEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_6->addWidget(label_3);

        subject_lineEdit = new QLineEdit(centralwidget);
        subject_lineEdit->setObjectName("subject_lineEdit");

        horizontalLayout_6->addWidget(subject_lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        upload_pushButton = new QPushButton(centralwidget);
        upload_pushButton->setObjectName("upload_pushButton");

        horizontalLayout_6->addWidget(upload_pushButton);

        horizontalLayout_6->setStretch(2, 1);
        horizontalLayout_6->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 2);
        verticalLayout->setStretch(3, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        ShortAnswerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ShortAnswerWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        ShortAnswerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ShortAnswerWindow);
        statusbar->setObjectName("statusbar");
        ShortAnswerWindow->setStatusBar(statusbar);

        retranslateUi(ShortAnswerWindow);

        QMetaObject::connectSlotsByName(ShortAnswerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ShortAnswerWindow)
    {
        ShortAnswerWindow->setWindowTitle(QCoreApplication::translate("ShortAnswerWindow", "MainWindow", nullptr));
        label_7->setText(QCoreApplication::translate("ShortAnswerWindow", "\347\256\200\347\255\224\351\242\230", nullptr));
        label->setText(QCoreApplication::translate("ShortAnswerWindow", "\351\242\230  \347\233\256", nullptr));
        label_2->setText(QCoreApplication::translate("ShortAnswerWindow", "\347\255\224  \346\241\210", nullptr));
        label_3->setText(QCoreApplication::translate("ShortAnswerWindow", "\347\247\221\347\233\256\357\274\232", nullptr));
        upload_pushButton->setText(QCoreApplication::translate("ShortAnswerWindow", "\344\270\212\344\274\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShortAnswerWindow: public Ui_ShortAnswerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTANSWERWINDOW_H

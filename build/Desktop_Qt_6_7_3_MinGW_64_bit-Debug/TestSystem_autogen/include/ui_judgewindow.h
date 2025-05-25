/********************************************************************************
** Form generated from reading UI file 'judgewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JUDGEWINDOW_H
#define UI_JUDGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JudgeWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QTextEdit *question_textEdit;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QRadioButton *correct_radioButton;
    QRadioButton *fault_radioButton_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *upload_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *JudgeWindow)
    {
        if (JudgeWindow->objectName().isEmpty())
            JudgeWindow->setObjectName("JudgeWindow");
        JudgeWindow->resize(800, 600);
        centralwidget = new QWidget(JudgeWindow);
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

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        correct_radioButton = new QRadioButton(centralwidget);
        correct_radioButton->setObjectName("correct_radioButton");

        horizontalLayout_5->addWidget(correct_radioButton);

        fault_radioButton_2 = new QRadioButton(centralwidget);
        fault_radioButton_2->setObjectName("fault_radioButton_2");

        horizontalLayout_5->addWidget(fault_radioButton_2);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_6->addWidget(label_2);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_6->addWidget(lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        upload_pushButton = new QPushButton(centralwidget);
        upload_pushButton->setObjectName("upload_pushButton");

        horizontalLayout_6->addWidget(upload_pushButton);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        JudgeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(JudgeWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        JudgeWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(JudgeWindow);
        statusbar->setObjectName("statusbar");
        JudgeWindow->setStatusBar(statusbar);

        retranslateUi(JudgeWindow);

        QMetaObject::connectSlotsByName(JudgeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *JudgeWindow)
    {
        JudgeWindow->setWindowTitle(QCoreApplication::translate("JudgeWindow", "MainWindow", nullptr));
        label_7->setText(QCoreApplication::translate("JudgeWindow", "\345\210\244\346\226\255\351\242\230", nullptr));
        label->setText(QCoreApplication::translate("JudgeWindow", "\351\242\230   \347\233\256", nullptr));
        label_6->setText(QCoreApplication::translate("JudgeWindow", "\347\255\224\346\241\210\357\274\232", nullptr));
        correct_radioButton->setText(QCoreApplication::translate("JudgeWindow", "\346\255\243\347\241\256", nullptr));
        fault_radioButton_2->setText(QCoreApplication::translate("JudgeWindow", "\351\224\231\350\257\257", nullptr));
        label_2->setText(QCoreApplication::translate("JudgeWindow", "\347\247\221\347\233\256\357\274\232", nullptr));
        upload_pushButton->setText(QCoreApplication::translate("JudgeWindow", "\344\270\212\344\274\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JudgeWindow: public Ui_JudgeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JUDGEWINDOW_H

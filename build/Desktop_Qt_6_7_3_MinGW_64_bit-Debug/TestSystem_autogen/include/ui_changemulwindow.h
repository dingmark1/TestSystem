/********************************************************************************
** Form generated from reading UI file 'changemulwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEMULWINDOW_H
#define UI_CHANGEMULWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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

class Ui_ChangeMulWindow
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
    QTextEdit *option1_textEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QTextEdit *option2_textEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QTextEdit *option3_textEdit_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QTextEdit *option4_textEdit_4;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QCheckBox *option1_checkBox;
    QCheckBox *option2_checkBox_2;
    QCheckBox *option3_checkBox_3;
    QCheckBox *option4_checkBox_4;
    QLabel *label_8;
    QLineEdit *subject_lineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *upload_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChangeMulWindow)
    {
        if (ChangeMulWindow->objectName().isEmpty())
            ChangeMulWindow->setObjectName("ChangeMulWindow");
        ChangeMulWindow->resize(800, 600);
        centralwidget = new QWidget(ChangeMulWindow);
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

        option1_textEdit = new QTextEdit(centralwidget);
        option1_textEdit->setObjectName("option1_textEdit");

        horizontalLayout->addWidget(option1_textEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        option2_textEdit_2 = new QTextEdit(centralwidget);
        option2_textEdit_2->setObjectName("option2_textEdit_2");

        horizontalLayout_2->addWidget(option2_textEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        option3_textEdit_3 = new QTextEdit(centralwidget);
        option3_textEdit_3->setObjectName("option3_textEdit_3");

        horizontalLayout_3->addWidget(option3_textEdit_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        option4_textEdit_4 = new QTextEdit(centralwidget);
        option4_textEdit_4->setObjectName("option4_textEdit_4");

        horizontalLayout_4->addWidget(option4_textEdit_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        option1_checkBox = new QCheckBox(centralwidget);
        option1_checkBox->setObjectName("option1_checkBox");

        horizontalLayout_5->addWidget(option1_checkBox);

        option2_checkBox_2 = new QCheckBox(centralwidget);
        option2_checkBox_2->setObjectName("option2_checkBox_2");

        horizontalLayout_5->addWidget(option2_checkBox_2);

        option3_checkBox_3 = new QCheckBox(centralwidget);
        option3_checkBox_3->setObjectName("option3_checkBox_3");

        horizontalLayout_5->addWidget(option3_checkBox_3);

        option4_checkBox_4 = new QCheckBox(centralwidget);
        option4_checkBox_4->setObjectName("option4_checkBox_4");

        horizontalLayout_5->addWidget(option4_checkBox_4);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");

        horizontalLayout_6->addWidget(label_8);

        subject_lineEdit = new QLineEdit(centralwidget);
        subject_lineEdit->setObjectName("subject_lineEdit");

        horizontalLayout_6->addWidget(subject_lineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        upload_pushButton = new QPushButton(centralwidget);
        upload_pushButton->setObjectName("upload_pushButton");

        horizontalLayout_6->addWidget(upload_pushButton);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);
        verticalLayout->setStretch(5, 1);
        verticalLayout->setStretch(6, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        ChangeMulWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChangeMulWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        ChangeMulWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ChangeMulWindow);
        statusbar->setObjectName("statusbar");
        ChangeMulWindow->setStatusBar(statusbar);

        retranslateUi(ChangeMulWindow);

        QMetaObject::connectSlotsByName(ChangeMulWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChangeMulWindow)
    {
        ChangeMulWindow->setWindowTitle(QCoreApplication::translate("ChangeMulWindow", "\344\277\256\346\224\271\351\242\230\347\233\256", nullptr));
        label_7->setText(QCoreApplication::translate("ChangeMulWindow", "\345\215\225\351\241\271\351\200\211\346\213\251\351\242\230", nullptr));
        label->setText(QCoreApplication::translate("ChangeMulWindow", "\351\242\230   \347\233\256", nullptr));
        label_2->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\344\270\200", nullptr));
        label_3->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\344\272\214", nullptr));
        label_4->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\344\270\211", nullptr));
        label_5->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\345\233\233", nullptr));
        label_6->setText(QCoreApplication::translate("ChangeMulWindow", "\347\255\224\346\241\210\357\274\232", nullptr));
        option1_checkBox->setText(QCoreApplication::translate("ChangeMulWindow", " \351\200\211\351\241\271\344\270\200", nullptr));
        option2_checkBox_2->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\344\272\214", nullptr));
        option3_checkBox_3->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\344\270\211", nullptr));
        option4_checkBox_4->setText(QCoreApplication::translate("ChangeMulWindow", "\351\200\211\351\241\271\345\233\233", nullptr));
        label_8->setText(QCoreApplication::translate("ChangeMulWindow", "\347\247\221\347\233\256\357\274\232", nullptr));
        upload_pushButton->setText(QCoreApplication::translate("ChangeMulWindow", "\344\270\212\344\274\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeMulWindow: public Ui_ChangeMulWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEMULWINDOW_H

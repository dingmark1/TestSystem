/********************************************************************************
** Form generated from reading UI file 'questionmanagewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTIONMANAGEWINDOW_H
#define UI_QUESTIONMANAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuestionManageWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *Question_TableWidget;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *content_lineEdit;
    QPushButton *query_pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *delete_pushButton_3;
    QPushButton *change_pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QuestionManageWindow)
    {
        if (QuestionManageWindow->objectName().isEmpty())
            QuestionManageWindow->setObjectName("QuestionManageWindow");
        QuestionManageWindow->resize(800, 600);
        centralwidget = new QWidget(QuestionManageWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        Question_TableWidget = new QTableWidget(centralwidget);
        if (Question_TableWidget->columnCount() < 4)
            Question_TableWidget->setColumnCount(4);
        QFont font;
        font.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        Question_TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Question_TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Question_TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Question_TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        Question_TableWidget->setObjectName("Question_TableWidget");
        Question_TableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        Question_TableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        Question_TableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        Question_TableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        Question_TableWidget->horizontalHeader()->setDefaultSectionSize(200);

        verticalLayout->addWidget(Question_TableWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        content_lineEdit = new QLineEdit(centralwidget);
        content_lineEdit->setObjectName("content_lineEdit");

        horizontalLayout->addWidget(content_lineEdit);

        query_pushButton = new QPushButton(centralwidget);
        query_pushButton->setObjectName("query_pushButton");

        horizontalLayout->addWidget(query_pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        delete_pushButton_3 = new QPushButton(centralwidget);
        delete_pushButton_3->setObjectName("delete_pushButton_3");

        horizontalLayout->addWidget(delete_pushButton_3);

        change_pushButton_2 = new QPushButton(centralwidget);
        change_pushButton_2->setObjectName("change_pushButton_2");

        horizontalLayout->addWidget(change_pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        QuestionManageWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QuestionManageWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        QuestionManageWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(QuestionManageWindow);
        statusbar->setObjectName("statusbar");
        QuestionManageWindow->setStatusBar(statusbar);

        retranslateUi(QuestionManageWindow);

        QMetaObject::connectSlotsByName(QuestionManageWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QuestionManageWindow)
    {
        QuestionManageWindow->setWindowTitle(QCoreApplication::translate("QuestionManageWindow", "\351\242\230\347\233\256\347\256\241\347\220\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Question_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("QuestionManageWindow", "\351\242\230\347\233\256id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Question_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("QuestionManageWindow", "\351\242\230\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Question_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("QuestionManageWindow", "\347\247\221\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = Question_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("QuestionManageWindow", "\347\261\273\345\210\253", nullptr));
        query_pushButton->setText(QCoreApplication::translate("QuestionManageWindow", "\346\237\245\350\257\242", nullptr));
        delete_pushButton_3->setText(QCoreApplication::translate("QuestionManageWindow", "\345\210\240\351\231\244", nullptr));
        change_pushButton_2->setText(QCoreApplication::translate("QuestionManageWindow", "\344\277\256\346\224\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuestionManageWindow: public Ui_QuestionManageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTIONMANAGEWINDOW_H

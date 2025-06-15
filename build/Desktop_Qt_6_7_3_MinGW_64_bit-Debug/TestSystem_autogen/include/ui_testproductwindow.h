/********************************************************************************
** Form generated from reading UI file 'testproductwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTPRODUCTWINDOW_H
#define UI_TESTPRODUCTWINDOW_H

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

class Ui_TestProductWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *Question_TableWidget;
    QTableWidget *Selected_TableWidget_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *content_lineEdit;
    QPushButton *query_pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *delete_pushButton_3;
    QPushButton *add_pushButton_2;
    QPushButton *finish_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TestProductWindow)
    {
        if (TestProductWindow->objectName().isEmpty())
            TestProductWindow->setObjectName("TestProductWindow");
        TestProductWindow->resize(800, 600);
        centralwidget = new QWidget(TestProductWindow);
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

        Selected_TableWidget_2 = new QTableWidget(centralwidget);
        if (Selected_TableWidget_2->columnCount() < 4)
            Selected_TableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        Selected_TableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Selected_TableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        Selected_TableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        Selected_TableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        Selected_TableWidget_2->setObjectName("Selected_TableWidget_2");
        Selected_TableWidget_2->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        Selected_TableWidget_2->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        Selected_TableWidget_2->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        Selected_TableWidget_2->horizontalHeader()->setCascadingSectionResizes(true);
        Selected_TableWidget_2->horizontalHeader()->setDefaultSectionSize(200);

        verticalLayout->addWidget(Selected_TableWidget_2);

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

        add_pushButton_2 = new QPushButton(centralwidget);
        add_pushButton_2->setObjectName("add_pushButton_2");

        horizontalLayout->addWidget(add_pushButton_2);

        finish_pushButton = new QPushButton(centralwidget);
        finish_pushButton->setObjectName("finish_pushButton");

        horizontalLayout->addWidget(finish_pushButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        TestProductWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TestProductWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        TestProductWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(TestProductWindow);
        statusbar->setObjectName("statusbar");
        TestProductWindow->setStatusBar(statusbar);

        retranslateUi(TestProductWindow);

        QMetaObject::connectSlotsByName(TestProductWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TestProductWindow)
    {
        TestProductWindow->setWindowTitle(QCoreApplication::translate("TestProductWindow", "\347\273\204\345\215\267\345\212\237\350\203\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Question_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TestProductWindow", "\351\242\230\347\233\256id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Question_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TestProductWindow", "\351\242\230\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Question_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TestProductWindow", "\347\247\221\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = Question_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TestProductWindow", "\347\261\273\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = Selected_TableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TestProductWindow", "\351\242\230\347\233\256id", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = Selected_TableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TestProductWindow", "\351\242\230\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = Selected_TableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("TestProductWindow", "\347\247\221\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = Selected_TableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("TestProductWindow", "\347\261\273\345\210\253", nullptr));
        query_pushButton->setText(QCoreApplication::translate("TestProductWindow", "\346\237\245\350\257\242", nullptr));
        delete_pushButton_3->setText(QCoreApplication::translate("TestProductWindow", "\345\210\240\351\231\244", nullptr));
        add_pushButton_2->setText(QCoreApplication::translate("TestProductWindow", "\345\212\240\345\205\245", nullptr));
        finish_pushButton->setText(QCoreApplication::translate("TestProductWindow", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestProductWindow: public Ui_TestProductWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTPRODUCTWINDOW_H

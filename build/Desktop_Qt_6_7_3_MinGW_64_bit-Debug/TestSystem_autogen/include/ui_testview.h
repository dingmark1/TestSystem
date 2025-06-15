/********************************************************************************
** Form generated from reading UI file 'testview.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTVIEW_H
#define UI_TESTVIEW_H

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

class Ui_TestView
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *Test_TableWidget;
    QTableWidget *Question_TableWidget_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *content_lineEdit;
    QPushButton *query_pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *view_pushButton_2;
    QPushButton *download_pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TestView)
    {
        if (TestView->objectName().isEmpty())
            TestView->setObjectName("TestView");
        TestView->resize(800, 600);
        centralwidget = new QWidget(TestView);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        Test_TableWidget = new QTableWidget(centralwidget);
        if (Test_TableWidget->columnCount() < 4)
            Test_TableWidget->setColumnCount(4);
        QFont font;
        font.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        Test_TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Test_TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Test_TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Test_TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        Test_TableWidget->setObjectName("Test_TableWidget");
        Test_TableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        Test_TableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        Test_TableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        Test_TableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        Test_TableWidget->horizontalHeader()->setDefaultSectionSize(200);

        verticalLayout->addWidget(Test_TableWidget);

        Question_TableWidget_2 = new QTableWidget(centralwidget);
        if (Question_TableWidget_2->columnCount() < 4)
            Question_TableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        Question_TableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Question_TableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        Question_TableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        Question_TableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        Question_TableWidget_2->setObjectName("Question_TableWidget_2");
        Question_TableWidget_2->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        Question_TableWidget_2->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        Question_TableWidget_2->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        Question_TableWidget_2->horizontalHeader()->setCascadingSectionResizes(true);
        Question_TableWidget_2->horizontalHeader()->setDefaultSectionSize(200);

        verticalLayout->addWidget(Question_TableWidget_2);

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

        view_pushButton_2 = new QPushButton(centralwidget);
        view_pushButton_2->setObjectName("view_pushButton_2");

        horizontalLayout->addWidget(view_pushButton_2);

        download_pushButton = new QPushButton(centralwidget);
        download_pushButton->setObjectName("download_pushButton");

        horizontalLayout->addWidget(download_pushButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        TestView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TestView);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        TestView->setMenuBar(menubar);
        statusbar = new QStatusBar(TestView);
        statusbar->setObjectName("statusbar");
        TestView->setStatusBar(statusbar);

        retranslateUi(TestView);

        QMetaObject::connectSlotsByName(TestView);
    } // setupUi

    void retranslateUi(QMainWindow *TestView)
    {
        TestView->setWindowTitle(QCoreApplication::translate("TestView", "\350\257\225\345\215\267\346\237\245\347\234\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Test_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TestView", "\350\257\225\345\215\267id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Test_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TestView", "\350\257\225\345\215\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Test_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TestView", "\347\247\221\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = Test_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TestView", "\345\210\233\345\273\272\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = Question_TableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TestView", "\351\242\230\347\233\256id", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = Question_TableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TestView", "\351\242\230\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = Question_TableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("TestView", "\347\247\221\347\233\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = Question_TableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("TestView", "\347\261\273\345\210\253", nullptr));
        query_pushButton->setText(QCoreApplication::translate("TestView", "\346\237\245\350\257\242", nullptr));
        view_pushButton_2->setText(QCoreApplication::translate("TestView", "\346\237\245\347\234\213", nullptr));
        download_pushButton->setText(QCoreApplication::translate("TestView", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestView: public Ui_TestView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTVIEW_H

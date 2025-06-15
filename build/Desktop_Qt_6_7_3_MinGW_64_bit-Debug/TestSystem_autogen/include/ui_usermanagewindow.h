/********************************************************************************
** Form generated from reading UI file 'usermanagewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGEWINDOW_H
#define UI_USERMANAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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

class Ui_UserManageWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *user_TableWidget;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *name_lineEdit;
    QComboBox *type_comboBox;
    QPushButton *query_pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *delete_pushButton_3;
    QPushButton *change_pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserManageWindow)
    {
        if (UserManageWindow->objectName().isEmpty())
            UserManageWindow->setObjectName("UserManageWindow");
        UserManageWindow->resize(800, 600);
        centralwidget = new QWidget(UserManageWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        user_TableWidget = new QTableWidget(centralwidget);
        if (user_TableWidget->columnCount() < 4)
            user_TableWidget->setColumnCount(4);
        QFont font;
        font.setKerning(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        user_TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        user_TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        user_TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        user_TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        user_TableWidget->setObjectName("user_TableWidget");
        user_TableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        user_TableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        user_TableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        user_TableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        user_TableWidget->horizontalHeader()->setDefaultSectionSize(200);

        verticalLayout->addWidget(user_TableWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        name_lineEdit = new QLineEdit(centralwidget);
        name_lineEdit->setObjectName("name_lineEdit");

        horizontalLayout->addWidget(name_lineEdit);

        type_comboBox = new QComboBox(centralwidget);
        type_comboBox->setObjectName("type_comboBox");

        horizontalLayout->addWidget(type_comboBox);

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

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        UserManageWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserManageWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 28));
        UserManageWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UserManageWindow);
        statusbar->setObjectName("statusbar");
        UserManageWindow->setStatusBar(statusbar);

        retranslateUi(UserManageWindow);

        QMetaObject::connectSlotsByName(UserManageWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserManageWindow)
    {
        UserManageWindow->setWindowTitle(QCoreApplication::translate("UserManageWindow", "\347\224\250\346\210\267\347\256\241\347\220\206", nullptr));
        QTableWidgetItem *___qtablewidgetitem = user_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("UserManageWindow", "\347\224\250\346\210\267id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = user_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("UserManageWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = user_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("UserManageWindow", "\347\224\250\346\210\267\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = user_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("UserManageWindow", "\346\263\250\345\206\214\346\227\266\351\227\264", nullptr));
        query_pushButton->setText(QCoreApplication::translate("UserManageWindow", "\346\237\245\350\257\242", nullptr));
        delete_pushButton_3->setText(QCoreApplication::translate("UserManageWindow", "\345\210\240\351\231\244", nullptr));
        change_pushButton_2->setText(QCoreApplication::translate("UserManageWindow", "\344\277\256\346\224\271", nullptr));
        pushButton->setText(QCoreApplication::translate("UserManageWindow", "\346\226\260\345\273\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManageWindow: public Ui_UserManageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGEWINDOW_H

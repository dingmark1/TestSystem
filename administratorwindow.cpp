#include "administratorwindow.h"
#include "ui_administratorwindow.h"
#include "usermanagewindow.h"
#include "testproductwindow.h"

AdministratorWindow::AdministratorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdministratorWindow)
{
    ui->setupUi(this);
}

AdministratorWindow::~AdministratorWindow()
{
    delete ui;
}

void AdministratorWindow::on_pushButton_clicked()
{
    UserManageWindow *usermanagewindow = new UserManageWindow(this);
    usermanagewindow -> show();
}


void AdministratorWindow::on_pushButton_2_clicked()
{
    TestProductWindow *testproductwindow = new TestProductWindow(this);
    testproductwindow -> show();
}


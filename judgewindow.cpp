#include "judgewindow.h"
#include "ui_judgewindow.h"

JudgeWindow::JudgeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JudgeWindow)
{
    ui->setupUi(this);
}

JudgeWindow::~JudgeWindow()
{
    delete ui;
}

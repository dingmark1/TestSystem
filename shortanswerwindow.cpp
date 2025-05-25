#include "shortanswerwindow.h"
#include "ui_shortanswerwindow.h"

ShortAnswerWindow::ShortAnswerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShortAnswerWindow)
{
    ui->setupUi(this);
}

ShortAnswerWindow::~ShortAnswerWindow()
{
    delete ui;
}

#include "judgewindow.h"
#include "ui_judgewindow.h"
#include <QMessageBox>
#include "userinfomanager.h"
#include "networkmanager.h"

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

void JudgeWindow::on_upload_pushButton_clicked()
{
    // 题目信息
    QString question = ui->question_textEdit->toPlainText();
    QString subject = ui->subject_lineEdit->text();
    int selectedOption = -1;
    if (ui->correct_radioButton->isChecked()) {
        selectedOption = 1;
    } else if (ui->fault_radioButton_2->isChecked()) {
        selectedOption = 2;
    }
    if (selectedOption == -1 || question.isEmpty() || subject.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }
    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();

    NetworkManager::instance().sendAddJudgeRequest(
        question,
        selectedOption,
        subject,
        uploader
        );

    disconnect(&NetworkManager::instance(), &NetworkManager::addSingleSelectFinished, this, nullptr);

    // 连接信号
    connect(&NetworkManager::instance(), &NetworkManager::addSingleSelectFinished,
            this, [=](bool success, const QString &msg){
                ui->upload_pushButton->setEnabled(true);
                QMessageBox::information(this, success ? "成功" : "错误", msg);
                if(success) {
                    ui->question_textEdit->clear();
                    ui->subject_lineEdit->clear();
                }
            });
}


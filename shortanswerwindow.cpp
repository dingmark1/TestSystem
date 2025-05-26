#include "shortanswerwindow.h"
#include "ui_shortanswerwindow.h"
#include <QMessageBox>
#include "userinfomanager.h"
#include "networkmanager.h"

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

void ShortAnswerWindow::on_upload_pushButton_clicked()
{
    ui->upload_pushButton->setEnabled(false);

    // 记录题目信息
    QString question = ui->question_textEdit->toPlainText();
    QString answer = ui->answer_textEdit->toPlainText();
    QString subject = ui->subject_lineEdit->text();
    if (answer.isEmpty() || question.isEmpty() || subject.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }

    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();

    NetworkManager::instance().sendAddShortAnswerRequest(
        question,
        answer,
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
                    ui->answer_textEdit->clear();
                    ui->subject_lineEdit->clear();
                }
            });

}


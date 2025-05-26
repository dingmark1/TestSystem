#include "mulselectwindow.h"
#include "ui_mulselectwindow.h"
#include <QMessageBox>
#include "userinfomanager.h"
#include "networkmanager.h"

MulSelectWindow::MulSelectWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MulSelectWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

MulSelectWindow::~MulSelectWindow()
{
    delete ui;
}

void MulSelectWindow::on_upload_pushButton_clicked()
{
    ui->upload_pushButton->setEnabled(false);

    // 记录题目信息
    QString question = ui->question_textEdit->toPlainText();
    QString option1 = ui->option1_textEdit->toPlainText();
    QString option2 = ui->option2_textEdit_2->toPlainText();
    QString option3 = ui->option3_textEdit_3->toPlainText();
    QString option4 = ui->option4_textEdit_4->toPlainText();
    QStringList options = {option1, option2, option3, option4};
    QString subject = ui->subject_lineEdit->text();
    int answer = ui->option1_checkBox->isChecked() * 8
               + ui->option2_checkBox_2->isChecked() * 4
               + ui->option3_checkBox_3->isChecked() * 2
               + ui->option4_checkBox_4->isChecked() * 1;

    if (answer == 0 || question.isEmpty() || option1.isEmpty() || option2.isEmpty() || option3.isEmpty() || option4.isEmpty() || subject.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }

    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();

    // 将信息发送至服务器，BASE_URL/add_mulselect
    // 发送请求
    NetworkManager::instance().sendAddMulSelectRequest(
        question,
        options,
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
                    ui->option1_textEdit->clear();
                    ui->option2_textEdit_2->clear();
                    ui->option3_textEdit_3->clear();
                    ui->option4_textEdit_4->clear();
                    ui->subject_lineEdit->clear();
                }
            });

}


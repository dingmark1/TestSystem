#include "singleselectwindow.h"
#include "ui_singleselectwindow.h"
#include <QMessageBox>
#include "userinfomanager.h"
#include "networkmanager.h"

SingleSelectWindow::SingleSelectWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SingleSelectWindow)
{
    ui->setupUi(this);
}

SingleSelectWindow::~SingleSelectWindow()
{
    delete ui;
}

void SingleSelectWindow::on_upload_pushButton_clicked()
{
    ui->upload_pushButton->setEnabled(false);

    // 记录题目信息
    QString question = ui->question_textEdit->toPlainText();
    QString option1 = ui->option1_textEdit->toPlainText();
    QString option2 = ui->option2_textEdit_2->toPlainText();
    QString option3 = ui->option3_textEdit_3->toPlainText();
    QString option4 = ui->option4_textEdit_4->toPlainText();
    int selectedOption = -1;
    if (ui->option1_radioButton->isChecked()) {
        selectedOption = 1;
    } else if (ui->option2_radioButton_2->isChecked()) {
        selectedOption = 2;
    } else if (ui->option3_radioButton_3->isChecked()) {
        selectedOption = 3;
    } else if (ui->option4_radioButton_4->isChecked()) {
        selectedOption = 4;
    }
    QString subject = ui->subject_lineEdit->text();

    if (selectedOption == -1 || question.isEmpty() || option1.isEmpty() || option2.isEmpty() || option3.isEmpty() || option4.isEmpty() || subject.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }

    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();

    // 整合信息，发送至服务器，BASE_URL/add_singleselect
    QStringList options = {option1, option2, option3, option4};

    // 发送请求
    NetworkManager::instance().sendAddSingleSelectRequest(
        question,
        options,
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
                    ui->option1_textEdit->clear();
                    ui->option2_textEdit_2->clear();
                    ui->option3_textEdit_3->clear();
                    ui->option4_textEdit_4->clear();
                    ui->subject_lineEdit->clear();
                }
            });

    // ui->upload_pushButton->setEnabled(true);
}


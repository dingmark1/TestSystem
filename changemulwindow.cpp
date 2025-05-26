#include "changemulwindow.h"
#include "ui_changemulwindow.h"
#include "networkmanager.h"
#include <QMessageBox>
#include "userinfomanager.h"

extern int target_ID;

ChangeMulWindow::ChangeMulWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChangeMulWindow)
{
    ui->setupUi(this);
}

ChangeMulWindow::~ChangeMulWindow()
{
    delete ui;
}

// 点击按钮上传修改后的多选题信息
void ChangeMulWindow::on_upload_pushButton_clicked()
{
    ui->upload_pushButton->setEnabled(false);

    // 记录题目信息
    QString question = ui->question_textEdit->toPlainText();
    QString option1 = ui->option1_textEdit->toPlainText();
    QString option2 = ui->option2_textEdit_2->toPlainText();
    QString option3 = ui->option3_textEdit_3->toPlainText();
    QString option4 = ui->option4_textEdit_4->toPlainText();
    int selectedOption = ui->option1_checkBox->isChecked() * 16
                        + ui->option2_checkBox_2->isChecked() * 8
                        + ui->option3_checkBox_3->isChecked() * 4
                        + ui->option4_checkBox_4->isChecked() * 2;
    QString subject = ui->subject_lineEdit->text();

    if (selectedOption == 0 || question.isEmpty() || option1.isEmpty() || option2.isEmpty() || option3.isEmpty() || option4.isEmpty() || subject.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }

    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();;

    QStringList options = {option1, option2, option3, option4};

    // 整合信息，发送至服务器，BASE_URL/change_mulselect
    // 发送请求
    NetworkManager::instance().sendchangeSingleSelectRequest(
        target_ID,
        question,
        options,
        selectedOption,
        subject,
        uploader
        );

    disconnect(&NetworkManager::instance(), &NetworkManager::changeSingleSelectFinished, this, nullptr);

    // 连接信号
    connect(&NetworkManager::instance(), &NetworkManager::changeSingleSelectFinished,
            this, [=](bool success, const QString &msg){
                ui->upload_pushButton->setEnabled(true);
                QMessageBox::information(this, success ? "成功" : "错误", msg);
                if(success) {
                    // 关闭窗口
                    this->close();
                }
            });

}

// 填充数据
void ChangeMulWindow::initData(int ID, const QString &question, const QStringList &options, int answer, const QString &subject) {
    ui->question_textEdit->setPlainText(question);
    ui->option1_textEdit->setPlainText(options.value(0));
    ui->option2_textEdit_2->setPlainText(options.value(1));
    ui->option3_textEdit_3->setPlainText(options.value(2));
    ui->option4_textEdit_4->setPlainText(options.value(3));

    // 解码答案
    bool option1 = (answer & 8) != 0;
    bool option2 = (answer & 4) != 0;
    bool option3 = (answer & 2) != 0;
    bool option4 = (answer & 1) != 0;

    ui->option1_checkBox->setChecked(option1);
    ui->option2_checkBox_2->setChecked(option2);
    ui->option3_checkBox_3->setChecked(option3);
    ui->option4_checkBox_4->setChecked(option4);

    ui->subject_lineEdit->setText(subject);

    target_ID = ID;
}

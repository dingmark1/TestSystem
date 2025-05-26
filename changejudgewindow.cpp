#include "changejudgewindow.h"
#include "ui_changejudgewindow.h"
#include <QMessageBox>
#include "networkmanager.h"
#include "userinfomanager.h"

extern int target_ID;

ChangeJudgeWindow::ChangeJudgeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChangeJudgeWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

ChangeJudgeWindow::~ChangeJudgeWindow()
{
    delete ui;
}

// 点击按钮上传修改后判断题
void ChangeJudgeWindow::on_upload_pushButton_clicked()
{
    ui->upload_pushButton->setEnabled(false);

    // 记录题目信息
    QString question = ui->question_textEdit->toPlainText();
    int answer = -1;
    if(ui->correct_radioButton->isChecked()){
        answer = 1;
    }else if(ui->fault_radioButton_2->isChecked()){
        answer = 0;
    }
    QString subject = ui->subject_lineEdit->text();

    if (answer == -1 || question.isEmpty() || subject.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }

    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();;

    // 整合信息，发送至服务器，BASE_URL/change_judge
    // 发送请求
    NetworkManager::instance().sendchangeJudgeRequest(
        target_ID,
        question,
        answer,
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
void ChangeJudgeWindow::initData(int ID, const QString &question, int answer, const QString &subject) {
    ui->question_textEdit->setPlainText(question);
    ui->subject_lineEdit->setText(subject);
    if(answer == 1){
        ui->correct_radioButton->setChecked(1);
    }else{
        ui->fault_radioButton_2->setChecked(1);
    }

    target_ID = ID;
}

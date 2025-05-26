#include "changeshortwindow.h"
#include "ui_changeshortwindow.h"
#include <QMessageBox>
#include "networkmanager.h"
#include "userinfomanager.h"

extern int target_ID;

ChangeShortWindow::ChangeShortWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChangeShortWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

ChangeShortWindow::~ChangeShortWindow()
{
    delete ui;
}

void ChangeShortWindow::on_upload_pushButton_clicked()
{
    ui->upload_pushButton->setEnabled(false);

    // 记录题目信息
    QString question = ui->question_textEdit->toPlainText();
    QString answer = ui->answer_textEdit->toPlainText();
    QString subject = ui->subject_lineEdit->text();

    if (subject.isEmpty() || question.isEmpty() || answer.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确保题目完整");
        ui->upload_pushButton->setEnabled(true);
        return;
    }

    // 当前用户信息
    QString uploader = UserInfoManager::instance().username();

    // 发送请求
    NetworkManager::instance().sendchangeShortRequest(
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
void ChangeShortWindow::initData(int ID, const QString &question, const QStringList &options, const QString &subject) {
    ui->question_textEdit->setPlainText(question);
    ui->answer_textEdit->setPlainText(options.value(0));
    ui->subject_lineEdit->setText(subject);

    target_ID = ID; // 这个ID来自于选中行中提取的信息。由于打开填充数据后，在上传时还会用到，所以用一个全局变量保存起来
}

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
    setAttribute(Qt::WA_DeleteOnClose);
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
        selectedOption = 0;
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


void JudgeWindow::on_pushButton_clicked()
{
    // 具体信息格式见singleselectwindow的AI请求部分

    QDialog dialog(this);
    dialog.setWindowTitle(tr("AI生成题目"));

    // 创建布局和控件
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLabel *label = new QLabel(tr("请输入您希望生成的题目描述:"), &dialog);
    QTextEdit *textEdit = new QTextEdit(&dialog); // 使用QTextEdit替代QLineEdit以支持多行输入
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    // 设置QTextEdit的大小
    textEdit->setMinimumSize(400, 200); // 设置最小宽度和高度

    // 将控件添加到布局
    layout->addWidget(label);
    layout->addWidget(textEdit);
    layout->addWidget(buttonBox);

    // 连接按钮信号
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 显示对话框并等待用户输入
    if (dialog.exec() != QDialog::Accepted || textEdit->toPlainText().isEmpty()) {
        return;
    }

    QString prompt = textEdit->toPlainText();

    // 创建并显示等待对话框
    QMessageBox *waitBox = new QMessageBox(this);
    waitBox->setWindowTitle("提示");
    waitBox->setText("正在生成题目...");
    waitBox->setStandardButtons(QMessageBox::NoButton);
    waitBox->setModal(true);
    waitBox->show();

    // 发送AI请求
    NetworkManager::instance().sendAIRequest(prompt, "judge");

    disconnect(&NetworkManager::instance(), &NetworkManager::aiRequestFinished, this, nullptr);

    // 连接信号处理响应
    QObject::connect(&NetworkManager::instance(), &NetworkManager::aiRequestFinished,
                    this, [=](bool success, const QString &msg,
                        const QString &question,
                        const QStringList &options,
                        int answer) {
                        waitBox->setText(success ? "  完成！ " : "题目生成失败，请重试");
                        waitBox->setStandardButtons(QMessageBox::Ok);

                        if (success) {
                            // 填充生成的题目到UI
                            ui->question_textEdit->setText(question);

                            // 设置正确答案
                            switch (answer) {
                            case 0: ui->fault_radioButton_2->setChecked(true); break;
                            case 1: ui->correct_radioButton->setChecked(true); break;
                            }
                        }

                        // 用户点击OK后删除对话框
                        QObject::connect(waitBox, &QMessageBox::finished, waitBox, &QMessageBox::deleteLater);
                    });
}


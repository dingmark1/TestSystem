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

// AI助手调用
void MulSelectWindow::on_pushButton_clicked()
{
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
    NetworkManager::instance().sendAIRequest(prompt, "single_select");

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
                             ui->option1_textEdit->setText(options.value(0, ""));
                             ui->option2_textEdit_2->setText(options.value(1, ""));
                             ui->option3_textEdit_3->setText(options.value(2, ""));
                             ui->option4_textEdit_4->setText(options.value(3, ""));

                             // 设置正确答案
                             // 解码答案
                             bool option1 = (answer & 8) != 0;
                             bool option2 = (answer & 4) != 0;
                             bool option3 = (answer & 2) != 0;
                             bool option4 = (answer & 1) != 0;

                             ui->option1_checkBox->setChecked(option1);
                             ui->option2_checkBox_2->setChecked(option2);
                             ui->option3_checkBox_3->setChecked(option3);
                             ui->option4_checkBox_4->setChecked(option4);
                         }

                         // 用户点击OK后删除对话框
                         QObject::connect(waitBox, &QMessageBox::finished, waitBox, &QMessageBox::deleteLater);
                     });
}


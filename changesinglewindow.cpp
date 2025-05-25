#include "changesinglewindow.h"
#include "ui_changesinglewindow.h"
#include "userinfomanager.h"
#include <QMessageBox>
#include "networkmanager.h"

int target_ID;

ChangeSingleWindow::ChangeSingleWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChangeSingleWindow)
{
    ui->setupUi(this);
}

ChangeSingleWindow::~ChangeSingleWindow()
{
    delete ui;
}

void ChangeSingleWindow::on_upload_pushButton_clicked()
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
    QString uploader = UserInfoManager::instance().username();;

    QStringList options = {option1, option2, option3, option4};

    // 整合信息，发送至服务器，BASE_URL/change_singleselect
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
void ChangeSingleWindow::initData(int ID, const QString &question, const QStringList &options, int answer, const QString &subject) {
    ui->question_textEdit->setPlainText(question);
    ui->option1_textEdit->setPlainText(options.value(0));
    ui->option2_textEdit_2->setPlainText(options.value(1));
    ui->option3_textEdit_3->setPlainText(options.value(2));
    ui->option4_textEdit_4->setPlainText(options.value(3));

    // 设置单选按钮
    QList<QRadioButton*> radios = {
        ui->option1_radioButton,
        ui->option2_radioButton_2,
        ui->option3_radioButton_3,
        ui->option4_radioButton_4
    };
    if (answer >= 1 && answer <= 4) {
        radios[answer-1]->setChecked(true);
    }

    ui->subject_lineEdit->setText(subject);

    target_ID = ID;
}


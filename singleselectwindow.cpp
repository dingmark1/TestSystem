#include "singleselectwindow.h"
#include "ui_singleselectwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include "userinfomanager.h"
#include "networkmanager.h"

SingleSelectWindow::SingleSelectWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SingleSelectWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
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
}

// 向AI提问，请求回答
void SingleSelectWindow::on_pushButton_clicked()
{
    // 弹出弹窗，要求用户输入希望生成的问题。
    // 输入完后，弹出提示窗1显示“正在生成题目...”，不允许用户手动关闭该提示窗。
    // 向后端BASE_URL/AI_request发送信息，包含用户输入的内容、目标题型
    // 等待直到获得来自后端的回答
    /* 服务器返回的题目json格式：
        {
            "question": "这是题目内容",
            "options": ["选项1", "选项2", "选项3", "选项4"],
            "answer": 数字1-4,
        }
        当然了，还有message字段表明是否生成成功
    */
    /* ！！！注意！！！
     * 由于所有题型的AI请求与返回都写在了一组函数里面，为了偷懒我就直接所有体题型全都用的单选题的这一套
     * 意味着无论什么题型，服务器返回的数据必须是上述的json格式
     * 对于多选题，形式完全一致。
     * 对于判断题，options的字段内容为空即可，但必须要有options字段。
     * 对于简答题，答案部分写在options的"选项一"字段处。
    */
    // 将得到的后端消息进行分析，提取出来问题、四个选项、答案，并填充到窗口中对应的文本框内，此时提示窗1显示“完成”，随后允许用户关闭该提示窗
    // 如果任何原因导致题目生成失败，则提示窗1显示“题目生成失败，请重试”，随后允许用户关闭该提示窗
    // 弹出输入对话框获取用户提示
    // 创建自定义对话框
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
                             switch (answer) {
                             case 1: ui->option1_radioButton->setChecked(true); break;
                             case 2: ui->option2_radioButton_2->setChecked(true); break;
                             case 3: ui->option3_radioButton_3->setChecked(true); break;
                             case 4: ui->option4_radioButton_4->setChecked(true); break;
                             }
                         }

                         // 用户点击OK后删除对话框
                         QObject::connect(waitBox, &QMessageBox::finished, waitBox, &QMessageBox::deleteLater);
                     });

}


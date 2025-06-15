#include "testview.h"
#include "ui_testview.h"
#include "networkmanager.h"
#include <QJsonArray>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

TestView::TestView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestView)
{
    ui->setupUi(this);

    // 设置表格为只读
    ui->Test_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Question_TableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置表格自适应拉伸
    ui->Test_TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Test_TableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->Question_TableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Question_TableWidget_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

TestView::~TestView()
{
    delete ui;
}

// 查询试卷
void TestView::on_query_pushButton_clicked()
{
    // 禁用所有控件
    setEnabled(false);

    // 获取查询信息
    QString content = ui->content_lineEdit->text();

    // 获取老师名字，这里先不分具体老师
    QString teachername = "_ALL_";

    // 清空表格
    ui->Test_TableWidget->clearContents();
    ui->Test_TableWidget->setRowCount(0);

    // 清空表格
    ui->Question_TableWidget_2->clearContents();
    ui->Question_TableWidget_2->setRowCount(0);

    // 先断开之前的连接
    disconnect(&NetworkManager::instance(), &NetworkManager::testQueryFinished,
               this, nullptr);

    // 连接信号槽
    connect(&NetworkManager::instance(), &NetworkManager::testQueryFinished,
            this, [this](bool success, const QString &message, const QJsonArray &testList) {
                if (!success) {
                    QMessageBox::warning(this, "查询失败", message);
                    return;
                }

                // 设置表格行数
                ui->Test_TableWidget->setRowCount(testList.size());

                // 填充表格数据
                for (int i = 0; i < testList.size(); ++i) {
                    QJsonObject test = testList[i].toObject();

                    QTableWidgetItem *idItem = new QTableWidgetItem(test["id"].toString());
                    QTableWidgetItem *nameItem = new QTableWidgetItem(test["testname"].toString());
                    QTableWidgetItem *subjectItem = new QTableWidgetItem(test["subject"].toString());
                    QTableWidgetItem *timeItem = new QTableWidgetItem(test["time"].toString());

                    ui->Test_TableWidget->setItem(i, 0, idItem);
                    ui->Test_TableWidget->setItem(i, 1, nameItem);
                    ui->Test_TableWidget->setItem(i, 2, subjectItem);
                    ui->Test_TableWidget->setItem(i, 3, timeItem);
                }
                // 启用所有控件
                setEnabled(true);
            });

    // 发送查询请求
    NetworkManager::instance().sendTestQueryRequest(content, teachername);
}

// 查询某一张试卷的具体内容
void TestView::on_view_pushButton_2_clicked()
{
    // 获取Test_TableWidget选中行的信息————要查询的试卷数据的id
    int currentRow = ui->Test_TableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中一行！");
        return;
    }
    QString id = ui->Test_TableWidget->item(currentRow, 0)->text();

    // 禁用所有控件
    setEnabled(false);

    // 清空题目表格
    ui->Question_TableWidget_2->clearContents();
    ui->Question_TableWidget_2->setRowCount(0);

    // 先断开之前的连接
    disconnect(&NetworkManager::instance(), &NetworkManager::testQuestionQueryFinished,
               this, nullptr);

    // 连接信号槽
    connect(&NetworkManager::instance(), &NetworkManager::testQuestionQueryFinished,
            this, [this](bool success, const QString &message, const QJsonArray &questionList) {
                if (!success) {
                    QMessageBox::warning(this, "查询失败", message);
                    setEnabled(true); // 恢复所有控件
                    return;
                }

                // 设置表格行数
                ui->Question_TableWidget_2->setRowCount(questionList.size());

                // 填充表格数据
                for (int i = 0; i < questionList.size(); ++i) {
                    QJsonObject question = questionList[i].toObject();

                    QTableWidgetItem *idItem = new QTableWidgetItem(question["id"].toString());
                    QTableWidgetItem *questionItem = new QTableWidgetItem(question["question"].toString());
                    QTableWidgetItem *subjectItem = new QTableWidgetItem(question["subject"].toString());
                    QTableWidgetItem *typeItem = new QTableWidgetItem(question["type"].toString());

                    ui->Question_TableWidget_2->setItem(i, 0, idItem);
                    ui->Question_TableWidget_2->setItem(i, 1, questionItem);
                    ui->Question_TableWidget_2->setItem(i, 2, subjectItem);
                    ui->Question_TableWidget_2->setItem(i, 3, typeItem);
                }

                // 启用所有控件
                setEnabled(true);
            });

    // 发送查询请求
    NetworkManager::instance().sendTestQuestionQueryRequest(id);
}

void TestView::on_download_pushButton_clicked()
{
    // 获取Question_TableWidget所有行的id信息
    int rowCount = ui->Question_TableWidget_2->rowCount();
    if (rowCount == 0) {
        QMessageBox::warning(this, "提示", "没有可导出的试卷！");
        return;
    }

    QStringList testIds;
    for (int i = 0; i < rowCount; ++i) {
        QString id = ui->Question_TableWidget_2->item(i, 0)->text();
        testIds.append(id);
    }

    // 禁用所有控件
    setEnabled(false);

    // 先断开之前的连接
    disconnect(&NetworkManager::instance(), &NetworkManager::downloadTestFinished,
               this, nullptr);

    // 连接信号槽
    connect(&NetworkManager::instance(), &NetworkManager::downloadTestFinished,
            this, [this](bool success, const QString &message, const QJsonArray &questionData) {
                // 启用所有控件
                setEnabled(true);

                if (!success) {
                    QMessageBox::warning(this, "导出失败", message);
                    return;
                }

                // 创建文件对话框让用户选择保存位置
                QString fileName = QFileDialog::getSaveFileName(this, "保存试卷", "导出的试卷.txt", "文本文件 (*.txt)");
                if (fileName.isEmpty()) {
                    return;
                }

                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QMessageBox::warning(this, "错误", "无法创建文件！");
                    return;
                }

                QTextStream out(&file);
                // Qt 6中不再使用setCodec，默认就是UTF-8编码

                // 写入试卷内容
                for (const QJsonValue &value : questionData) {
                    QJsonObject question = value.toObject();
                    QString type = question["type"].toString();
                    QString questionText = question["question"].toString();

                    out << "【" << type << "】" << "\n";
                    out << questionText << "\n";

                    if (type == "单选题" || type == "多选题") {
                        QJsonArray options = question["options"].toArray();
                        for (int i = 0; i < options.size(); ++i) {
                            out << QString("%1. %2\n").arg(QChar('A' + i)).arg(options[i].toString());
                        }
                    } else if (type == "判断题") {
                        out << "A. 正确\n";
                        out << "B. 错误\n";
                    }

                    out << "\n"; // 题目间空一行
                }

                file.close();
                QMessageBox::information(this, "成功", "试卷导出成功！");
            });

    // 发送下载请求
    NetworkManager::instance().sendDownloadTestRequest(testIds);
}

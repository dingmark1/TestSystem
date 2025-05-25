#include "testproductwindow.h"
#include "ui_testproductwindow.h"
#include "networkmanager.h"
#include <QJsonArray>
#include <QMessageBox>
#include "userinfomanager.h"
#include <QInputDialog>

TestProductWindow::TestProductWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestProductWindow)
{
    ui->setupUi(this);
    // 设置表格自适应拉伸
    ui->Question_TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Question_TableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 连接查询结果信号
    connect(&NetworkManager::instance(), &NetworkManager::queryFinished,
            this, &TestProductWindow::handleQueryFinished);

    // 试卷上传信号
    connect(&NetworkManager::instance(), &NetworkManager::addTestFinished,
            this, &TestProductWindow::handleAddTestFinished);
}

TestProductWindow::~TestProductWindow()
{
    delete ui;
}

// 功能函数实现区域
// 上传处理函数
void TestProductWindow::handleAddTestFinished(bool success, const QString &message) {
    setEnabled(true); // 恢复所有控件
    if(success) {
        QMessageBox::information(this, "成功", "试卷上传成功");
        ui->Selected_TableWidget_2->setRowCount(0); // 清空已选题目
    } else {
        QMessageBox::warning(this, "上传失败", message);
    }
    ui->finish_pushButton->setEnabled(true);
}

void TestProductWindow::handleQueryFinished(bool success, const QString &message, const QJsonArray &questionList) {
    if (success) {
        ui->Question_TableWidget->clearContents();
        ui->Question_TableWidget->setRowCount(questionList.size());

        for (int i = 0; i < questionList.size(); ++i) {
            QJsonObject obj = questionList[i].toObject();
            QTableWidgetItem *idItem = new QTableWidgetItem(obj["id"].toString());
            QTableWidgetItem *contentItem = new QTableWidgetItem(obj["question"].toString());
            QTableWidgetItem *subjectItem = new QTableWidgetItem(obj["subject"].toString());
            QTableWidgetItem *typeItem = new QTableWidgetItem(obj["type"].toString());

            ui->Question_TableWidget->setItem(i, 0, idItem);
            ui->Question_TableWidget->setItem(i, 1, contentItem);
            ui->Question_TableWidget->setItem(i, 2, subjectItem);
            ui->Question_TableWidget->setItem(i, 3, typeItem);
        }
    } else {
        QMessageBox::warning(this, "查询失败", message);
    }
}

// 查询题目
void TestProductWindow::on_query_pushButton_clicked()
{
    //获取查询信息
    QString content = ui->content_lineEdit->text();

    // 获取老师名字
    QString teachername = "_ALL_";

    // TODO:使用content和teachername信息向服务器BASE_URL/query_question发出查询请求。
    // 服务器返回符合要求的题目的id、题目简述、对应科目、题目类型（单选/多选/判断/简答）。
    // 清空Question_TableWidget，并将新获取到的题目信息罗列在Question_TableWidget里面。
    NetworkManager::instance().sendQueryRequest(content, teachername);
}

// 加入试题功能
// 将Question_TableWidget中的选中的一行加入到Selected_TableWidget_2中
void TestProductWindow::on_add_pushButton_2_clicked()
{
    // 禁用按钮防止重复点击,需要在后面重新启用
    ui->add_pushButton_2->setEnabled(false);

    // 获取Question_TableWidget的选中行的信息————待加入的题目数据的id
    int currentRow = ui->Question_TableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中Question_TableWidget的一行！");
        ui->add_pushButton_2->setEnabled(true);
        return;
    }

    // 通过id检查选中行是否已经存在于Selected_TableWidget_2中
        // 如果已经存在，提示“重复题目”
        // 如果不存在，将选中行加入到Selected_TableWidget_2中

    // 获取选中行的ID
    QString selectedId = ui->Question_TableWidget->item(currentRow, 0)->text();

    // 检查是否已存在重复ID
    bool exists = false;
    int rowCount = ui->Selected_TableWidget_2->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        if (ui->Selected_TableWidget_2->item(i, 0)->text() == selectedId) {
            exists = true;
            break;
        }
    }

    if (exists) {
        QMessageBox::warning(this, "提示", "重复题目！");
        ui->add_pushButton_2->setEnabled(true);
        return;
    }

    // 添加新行到Selected_TableWidget_2
    int newRow = ui->Selected_TableWidget_2->rowCount();
    ui->Selected_TableWidget_2->insertRow(newRow);

    // 复制所有列的数据（深拷贝）
    for (int col = 0; col < 4; ++col) {
        QTableWidgetItem *srcItem = ui->Question_TableWidget->item(currentRow, col);
        QTableWidgetItem *newItem = new QTableWidgetItem(*srcItem); // 复制内容
        ui->Selected_TableWidget_2->setItem(newRow, col, newItem);
    }

    ui->add_pushButton_2->setEnabled(true);
}

// 删除已选择的题目
// 将Selected_TableWidget_2中被选中的一行删去
void TestProductWindow::on_delete_pushButton_3_clicked()
{
    // 禁用按钮防止重复点击,需要在后面重新启用
    ui->delete_pushButton_3->setEnabled(false);

    // 获取Selected_TableWidget_2的选中行的信息
    int currentRow = ui->Selected_TableWidget_2->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中Selected_TableWidget_2的一行！");
        ui->delete_pushButton_3->setEnabled(true);
        return;
    }

    // 删去选中这一行
    // 禁用所有控件
    setEnabled(false);

    ui->Selected_TableWidget_2->removeRow(currentRow);

    // 启用所有控件
    ui->delete_pushButton_3->setEnabled(true);
    setEnabled(true);
}

// 上传试卷
void TestProductWindow::on_finish_pushButton_clicked()
{
    ui->finish_pushButton->setEnabled(false);
    QString uploader = UserInfoManager::instance().username();

    // 收集题目ID
    QJsonArray questionIds;
    int rowCount = ui->Selected_TableWidget_2->rowCount();
    for(int i = 0; i < rowCount; ++i) {
        QString id = ui->Selected_TableWidget_2->item(i, 0)->text();
        questionIds.append(id);
    }

    if(questionIds.isEmpty()) {
        QMessageBox::warning(this, "提示", "请至少选择一道题目");
        ui->finish_pushButton->setEnabled(true);
        return;
    }

    // 获取试卷名称
    bool ok;
    QString testName = QInputDialog::getText(this, "试卷名称",
                                             "请输入试卷名称：",
                                             QLineEdit::Normal,
                                             "", &ok);
    if(!ok || testName.isEmpty()) {
        ui->finish_pushButton->setEnabled(true);
        return;
    }

    setEnabled(false); // 禁用所有控件
    NetworkManager::instance().sendAddTestRequest(testName, uploader, questionIds);
}



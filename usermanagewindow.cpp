#include "usermanagewindow.h"
#include "ui_usermanagewindow.h"
#include "networkmanager.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QInputDialog>

UserManageWindow::UserManageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserManageWindow)
{
    ui->setupUi(this);

    ui->type_comboBox->addItem("全部");
    ui->type_comboBox->addItem("学生");
    ui->type_comboBox->addItem("老师");
    ui->type_comboBox->addItem("管理员");

    // 设置表格为只读
    ui->user_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置表头自适应拉伸模式（平均填充）,确保表格本身填满布局空间
    ui->user_TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->user_TableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 查询用户功能
    connect(&NetworkManager::instance(), &NetworkManager::userqueryFinished,
            this, &UserManageWindow::handleuserQueryFinished);

    setAttribute(Qt::WA_DeleteOnClose);
}

UserManageWindow::~UserManageWindow()
{
    delete ui;
}


// 查询功能
void UserManageWindow::on_query_pushButton_clicked()
{
    // 获取查询信息
    QString content = ui->name_lineEdit->text();
    QString type = ui->type_comboBox->currentText();

    //
    NetworkManager::instance().senduserQueryRequest(content, type);
}

void UserManageWindow::handleuserQueryFinished(bool success, const QString &message, const QJsonArray &userList) {
    if (success) {
        ui->user_TableWidget->clearContents();
        ui->user_TableWidget->setRowCount(userList.size());

        for (int i = 0; i < userList.size(); ++i) {
            QJsonObject obj = userList[i].toObject();
            QTableWidgetItem *idItem = new QTableWidgetItem(obj["id"].toString());
            QTableWidgetItem *nameItem = new QTableWidgetItem(obj["name"].toString());
            QTableWidgetItem *typeItem = new QTableWidgetItem(obj["type"].toString());
            QTableWidgetItem *timeItem = new QTableWidgetItem(obj["time"].toString());

            ui->user_TableWidget->setItem(i, 0, idItem);
            ui->user_TableWidget->setItem(i, 1, nameItem);
            ui->user_TableWidget->setItem(i, 2, typeItem);
            ui->user_TableWidget->setItem(i, 3, timeItem);
        }
    } else {
        QMessageBox::warning(this, "查询失败", message);
    }
}

// 删除选中用户
void UserManageWindow::on_delete_pushButton_3_clicked()
{
    ui->delete_pushButton_3->setEnabled(false);

    // 获取选中行的信息————待删除的用户数据的id
    int currentRow = ui->user_TableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中一行！");
        ui->delete_pushButton_3->setEnabled(true);
        return;
    }
    QString id = ui->user_TableWidget->item(currentRow, 0)->text();      // 第0列：用户ID

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  "确定要删除选中的题目吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        ui->delete_pushButton_3->setEnabled(true);
        return;
    }

    // 禁用所有控件
    setEnabled(false);
    // 保持选中状态
    ui->user_TableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->user_TableWidget->selectRow(currentRow);

    disconnect(&NetworkManager::instance(), &NetworkManager::userdeleteFinished, this, nullptr);

    // 连接删除完成信号
    connect(&NetworkManager::instance(), &NetworkManager::userdeleteFinished,
            this, [=](bool success, const QString &message) {
                // 恢复控件状态
                setEnabled(true);
                ui->user_TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                ui->delete_pushButton_3->setEnabled(true);

                if (success) {
                    // 从表格中移除行
                    ui->user_TableWidget->removeRow(currentRow);
                    QMessageBox::information(this, "成功", "用户删除成功");
                } else {
                    QMessageBox::warning(this, "失败", message);
                }
            });

    // 发送删除请求
    NetworkManager::instance().senduserDeleteRequest(id);

}


// 新建用户
void UserManageWindow::on_pushButton_clicked()
{
    // 弹窗输入用户名
    bool ok;
    QString name = QInputDialog::getText(this, "新建用户",
                                         "请输入用户名：",
                                         QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) {
        QMessageBox::information(this, "提示", "操作取消");
        return;
    }

    // 弹窗选择身份类型
    QStringList types;
    types << "学生" << "老师" << "管理员";
    QString type = QInputDialog::getItem(this, "选择身份",
                                         "请选择用户类型：",
                                         types, 0, false, &ok);
    if (!ok || type.isEmpty()) {
        QMessageBox::information(this, "提示", "操作取消");
        return;
    }

    if(name.isEmpty() || type.isEmpty()){
        QMessageBox::information(this, "提示", "操作取消");
        return;
    }

    // 弹窗输入密码
    QString code = QInputDialog::getText(this, "新建用户",
                                         "请输入密码：",
                                         QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) {
        QMessageBox::information(this, "提示", "操作取消");
        return;
    }

    disconnect(&NetworkManager::instance(), &NetworkManager::userAddFinished, this, nullptr);

    // 连接新增完成信号
    connect(&NetworkManager::instance(), &NetworkManager::userAddFinished,
            this, [=](bool success, const QString &message) {
                if (success) {
                    QMessageBox::information(this, "成功", "用户新增成功");
                } else {
                    QMessageBox::warning(this, "错误", message);
                }
                // 启用所有控件
                setEnabled(true);
            });

    // 禁用所有控件
    setEnabled(false);

    // 发送新增请求
    NetworkManager::instance().senduserAddRequest(name, type, code);

}

// 修改用户信息
void UserManageWindow::on_change_pushButton_2_clicked()
{

}


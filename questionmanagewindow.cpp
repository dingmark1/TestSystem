#include "questionmanagewindow.h"
#include "ui_questionmanagewindow.h"
#include "userinfomanager.h"
#include "networkmanager.h"
#include <QJsonArray>
#include <QMessageBox>
#include <QDebug>
#include "changesinglewindow.h"
#include "changemulwindow.h"

QuestionManageWindow::QuestionManageWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QuestionManageWindow)
{
    ui->setupUi(this);

    // 设置表头自适应拉伸模式（平均填充）
    ui->Question_TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 确保表格本身填满布局空间
    ui->Question_TableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 查询功能
    connect(&NetworkManager::instance(), &NetworkManager::queryFinished,
            this, &QuestionManageWindow::handleQueryFinished);

    setWindowFlags(Qt::Window);
}

// 处理查询结果的函数
void QuestionManageWindow::handleQueryFinished(bool success, const QString &message, const QJsonArray &questionList) {
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

QuestionManageWindow::~QuestionManageWindow()
{
    delete ui;
}

// 向服务器查询题目列表并展示
void QuestionManageWindow::on_query_pushButton_clicked()
{

    //获取查询信息
    QString content = ui->content_lineEdit->text();

    // 获取老师名字
    QString teachername = UserInfoManager::instance().username();

    // TODO:使用content和teachername信息向服务器BASE_URL/query_question发出查询请求。
    // 服务器返回符合要求的题目的id、题目简述、对应科目、题目类型（单选/多选/判断/简答）。
    // 清空Question_TableWidget，并将新获取到的题目信息罗列在Question_TableWidget里面。
    NetworkManager::instance().sendQueryRequest(content, teachername);

}

// 删除选定行的数据
void QuestionManageWindow::on_delete_pushButton_3_clicked()
{
    // 禁用按钮防止重复点击,需要在后面重新启用
    ui->delete_pushButton_3->setEnabled(false);

    // 获取选中行的信息————待删除的题目数据的id
    int currentRow = ui->Question_TableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中一行！");
        ui->delete_pushButton_3->setEnabled(true);
        return;
    }
    QString id = ui->Question_TableWidget->item(currentRow, 0)->text();      // 第0列：题目ID

    // 保险措施：弹出窗口询问是否删除
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
    ui->Question_TableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->Question_TableWidget->selectRow(currentRow);

    disconnect(&NetworkManager::instance(), &NetworkManager::deleteFinished, this, nullptr);

    // 连接删除完成信号
    connect(&NetworkManager::instance(), &NetworkManager::deleteFinished,
            this, [=](bool success, const QString &message) {
                // 恢复控件状态
                setEnabled(true);
                ui->Question_TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                ui->delete_pushButton_3->setEnabled(true);

                if (success) {
                    // 从表格中移除行
                    ui->Question_TableWidget->removeRow(currentRow);
                    QMessageBox::information(this, "成功", "题目删除成功");
                } else {
                    QMessageBox::warning(this, "删除失败", message);
                }
            });

    // 发送删除请求
    NetworkManager::instance().sendDeleteRequest(id);
}

// 修改功能
void QuestionManageWindow::on_change_pushButton_2_clicked()
{
    qDebug() << "change_pushButton clicked";
    // 禁用所有控件
    setEnabled(false);

    // 获取选中行的信息————待修改的题目数据的id
    int currentRow = ui->Question_TableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中一行！");
        setEnabled(true); // 恢复所有控件
        return;
    }
    QString id = ui->Question_TableWidget->item(currentRow, 0)->text();     // 第0列：题目ID
    QString type = ui->Question_TableWidget->item(currentRow, 3)->text();   // 第3列：题目类型

    // 根据type字段分题型操作
    if(type == "单选题"){
        /*服务器返回的单选题json格式：
        {
            "question": "这是题目内容",
            "options": ["选项1", "选项2", "选项3", "选项4"],
            "answer": 数字1-4,
            "subject": "这是学科",
        }
        */
        // 使用id向服务器BASE_URL/specific_singlequestion请求对应题目的信息。并将信息进行保存在相应变量中
        QString question;
        QString option1, option2, option3, option4;
        int answer;
        QString subject;

        // 连接信号处理
        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(&NetworkManager::instance(), &NetworkManager::specificSingleSelectReceived,
                        this, [=](bool success, const QString &msg,
                            const QString &q, const QStringList &opts,
                            int ans, const QString &subj) mutable {

                            if(success){
                                // 保存获取到的题目信息
                                question = q;
                                option1 = opts.value(0, "");
                                option2 = opts.value(1, "");
                                option3 = opts.value(2, "");
                                option4 = opts.value(3, "");
                                answer = ans;
                                subject = subj;

                                // 打开一个新ChangeSingleWindow窗口，并将保存的数据question、option1-4、answer、subject填入新窗口的对应部分。
                                // 创建并填充修改窗口
                                ChangeSingleWindow *editWindow = new ChangeSingleWindow(this);
                                QStringList options = {option1, option2, option3, option4};
                                editWindow->initData(id.toInt(), question, options, answer, subject);
                                editWindow->show();
                            } else {
                                qDebug() << "获取失败";
                                QMessageBox::warning(this, "提示", "题目获取失败");
                            }

                            disconnect(*conn); // 断开信号连接
                        });

        // 发送请求
        NetworkManager::instance().sendSpecificSingleSelectRequest(id);

    }else if(type == "多选题"){
        /*服务器返回的单选题json格式，与单选题一致：
        {
            "question": "这是题目内容",
            "options": ["选项1", "选项2", "选项3", "选项4"],
            "answer": 数字,
            "subject": "这是学科",
        }
        */
        // 使用id向服务器BASE_URL/specific_mulquestion请求对应题目的信息。并将信息进行保存在相应变量中
        QString question;
        QString option1, option2, option3, option4;
        int answer;
        QString subject;

        // 连接信号处理
        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(&NetworkManager::instance(), &NetworkManager::specificSingleSelectReceived,
                        this, [=](bool success, const QString &msg,
                            const QString &q, const QStringList &opts,
                            int ans, const QString &subj) mutable {

                            if(success){
                                // 保存获取到的题目信息
                                question = q;
                                option1 = opts.value(0, "");
                                option2 = opts.value(1, "");
                                option3 = opts.value(2, "");
                                option4 = opts.value(3, "");
                                answer = ans;
                                subject = subj;

                                // 打开一个新ChangeSingleWindow窗口，并将保存的数据question、option1-4、answer、subject填入新窗口的对应部分。
                                // 创建并填充修改窗口
                                ChangeMulWindow *editWindow = new ChangeMulWindow(this);
                                QStringList options = {option1, option2, option3, option4};
                                editWindow->initData(id.toInt(), question, options, answer, subject);
                                editWindow->show();
                            } else {
                                qDebug() << "获取失败";
                                QMessageBox::warning(this, "提示", "题目获取失败");
                            }

                            disconnect(*conn); // 断开信号连接
                        });

        // 发送请求
        NetworkManager::instance().sendSpecificMulSelectRequest(id);

    }else if(type == "判断题"){
        // 是判断题

    }else{
        // 是简答题

    }

    setEnabled(true); // 恢复所有控件
}


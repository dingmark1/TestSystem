#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "teacherwindow.h"
#include "administratorwindow.h"
#include "userinfomanager.h"
#include "studentwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 初始化用户类型下拉框
    ui->Usertype_comboBox->addItem("学生");
    ui->Usertype_comboBox->addItem("老师");
    ui->Usertype_comboBox->addItem("管理员");

    // 连接网络管理器的登录完成信号到处理函数
    connect(&NetworkManager::instance(), &NetworkManager::loginFinished,
            this, &MainWindow::handleLoginResponse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 登录按钮点击事件处理
void MainWindow::on_Login_pushButton_clicked()
{
    ui->Login_pushButton->setEnabled(false);  // 禁用登录按钮防止重复点击
    QString usertype = ui->Usertype_comboBox->currentText();
    QString username = ui->Username_lineEdit->text();
    QString code = ui->Code_lineEdit_2->text();

    UserInfoManager::instance().setUsername(username);

    if(username.isEmpty() || code.isEmpty()){
        // 测试teacher窗口用（实际应删除这段测试代码）
        // AdministratorWindow *administrator = new AdministratorWindow(this);
        // administrator -> show();
        // this -> hide();

        ui->prompt_label_5->setText("用户名或密码不能为空");
        ui->Login_pushButton->setEnabled(true);
        return;
    }

    ui->prompt_label_5->setText("登录中...");
    NetworkManager::instance().sendLoginRequest(usertype, username, code);
}

// 处理登录响应
void MainWindow::handleLoginResponse(bool success, const QString &message, const QJsonObject &data)
{
    if(success){
        //QMessageBox::information(this, "登录成功", message);
        //ui->prompt_label_5->setText("登录成功");
        //QString userType = data.value("user_type").toString();
        QString userType = ui->Usertype_comboBox->currentText();
        ui->prompt_label_5->setText("");
        ui->Username_lineEdit->setText("");
        ui->Code_lineEdit_2->setText("");

        // 根据用户类型跳转到对应界面
        if(userType == "老师"){
            TeacherWindow *teacherWindow = new TeacherWindow();
            teacherWindow->setAttribute(Qt::WA_DeleteOnClose);
            connect(teacherWindow, &TeacherWindow::destroyed, this, &MainWindow::show);
            teacherWindow->show();
            this->hide();
        }else if(userType == "学生"){
            // TODO: 学生界面跳转
            StudentWindow *studentWindow = new StudentWindow();
            studentWindow->setAttribute(Qt::WA_DeleteOnClose);
            connect(studentWindow, &StudentWindow::destroyed, this, &MainWindow::show);
            studentWindow->show();
            this->hide();
        }else{
            AdministratorWindow *administrator = new AdministratorWindow();
            administrator->setAttribute(Qt::WA_DeleteOnClose);
            connect(administrator, &AdministratorWindow::destroyed, this, &MainWindow::show);
            administrator -> show();
            this -> hide();
        }

    }else{
        ui->prompt_label_5->setText(message);  // 显示错误信息
    }

    ui->Login_pushButton->setEnabled(true);  // 重新启用登录按钮
}

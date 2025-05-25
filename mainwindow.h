#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QJsonObject>
#include "networkmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// 主窗口类
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 登录按钮点击槽函数
    void on_Login_pushButton_clicked();
    // 登录响应处理槽函数
    void handleLoginResponse(bool success, const QString &message, const QJsonObject &data);

private:
    Ui::MainWindow *ui;  // UI界面指针
};
#endif // MAINWINDOW_H

#ifndef USERMANAGEWINDOW_H
#define USERMANAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserManageWindow;
}

class UserManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserManageWindow(QWidget *parent = nullptr);
    ~UserManageWindow();

private slots:
    void on_query_pushButton_clicked();
    void handleuserQueryFinished(bool success, const QString &message, const QJsonArray &questionList);

    void on_delete_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_change_pushButton_2_clicked();

private:
    Ui::UserManageWindow *ui;
};

#endif // USERMANAGEWINDOW_H

#ifndef QUESTIONMANAGEWINDOW_H
#define QUESTIONMANAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class QuestionManageWindow;
}

class QuestionManageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuestionManageWindow(QWidget *parent = nullptr);
    ~QuestionManageWindow();

private slots:
    void on_query_pushButton_clicked();

    // 处理查询结果
    void handleQueryFinished(bool success, const QString &message, const QJsonArray &questionList);

    void on_delete_pushButton_3_clicked();

    void on_change_pushButton_2_clicked();

private:
    Ui::QuestionManageWindow *ui;
};

#endif // QUESTIONMANAGEWINDOW_H

#ifndef CHANGEJUDGEWINDOW_H
#define CHANGEJUDGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChangeJudgeWindow;
}

class ChangeJudgeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeJudgeWindow(QWidget *parent = nullptr);
    void initData(int ID, const QString &question, int answer, const QString &subject);

    ~ChangeJudgeWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::ChangeJudgeWindow *ui;
};

#endif // CHANGEJUDGEWINDOW_H

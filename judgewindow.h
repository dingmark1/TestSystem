#ifndef JUDGEWINDOW_H
#define JUDGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class JudgeWindow;
}

class JudgeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JudgeWindow(QWidget *parent = nullptr);
    ~JudgeWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::JudgeWindow *ui;
};

#endif // JUDGEWINDOW_H

#ifndef UPLOADQUESTIONWINDOW_H
#define UPLOADQUESTIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class UploadQuestionWindow;
}

class UploadQuestionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UploadQuestionWindow(QWidget *parent = nullptr);
    ~UploadQuestionWindow();

private slots:
    void on_singleselect_pushButton_clicked();

    void on_mulselect_pushButton_2_clicked();

    void on_judge_pushButton_3_clicked();

    void on_short_pushButton_4_clicked();

private:
    Ui::UploadQuestionWindow *ui;
};

#endif // UPLOADQUESTIONWINDOW_H

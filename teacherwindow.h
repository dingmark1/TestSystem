#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = nullptr);
    ~TeacherWindow();

private slots:
    void on_pushButton_clicked();

    void on_manage_pushButton_2_clicked();

    void on_upload_pushButton_clicked();

private:
    Ui::TeacherWindow *ui;
};

#endif // TEACHERWINDOW_H

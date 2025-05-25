#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdministratorWindow;
}

class AdministratorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdministratorWindow(QWidget *parent = nullptr);
    ~AdministratorWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AdministratorWindow *ui;
};

#endif // ADMINISTRATORWINDOW_H

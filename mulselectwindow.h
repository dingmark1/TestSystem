#ifndef MULSELECTWINDOW_H
#define MULSELECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class MulSelectWindow;
}

class MulSelectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MulSelectWindow(QWidget *parent = nullptr);
    ~MulSelectWindow();

private slots:
    void on_upload_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MulSelectWindow *ui;
};

#endif // MULSELECTWINDOW_H

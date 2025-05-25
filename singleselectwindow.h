#ifndef SINGLESELECTWINDOW_H
#define SINGLESELECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class SingleSelectWindow;
}

class SingleSelectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingleSelectWindow(QWidget *parent = nullptr);
    ~SingleSelectWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::SingleSelectWindow *ui;
};

#endif // SINGLESELECTWINDOW_H

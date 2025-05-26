#ifndef SHORTANSWERWINDOW_H
#define SHORTANSWERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ShortAnswerWindow;
}

class ShortAnswerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShortAnswerWindow(QWidget *parent = nullptr);
    ~ShortAnswerWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::ShortAnswerWindow *ui;
};

#endif // SHORTANSWERWINDOW_H

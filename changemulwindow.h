#ifndef CHANGEMULWINDOW_H
#define CHANGEMULWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChangeMulWindow;
}

class ChangeMulWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeMulWindow(QWidget *parent = nullptr);
    void initData(int ID, const QString &question, const QStringList &options, int answer, const QString &subject);

    ~ChangeMulWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::ChangeMulWindow *ui;
};

#endif // CHANGEMULWINDOW_H

#ifndef CHANGESHORTWINDOW_H
#define CHANGESHORTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChangeShortWindow;
}

class ChangeShortWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeShortWindow(QWidget *parent = nullptr);
    void initData(int ID, const QString &question, const QStringList &options, const QString &subject);


    ~ChangeShortWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::ChangeShortWindow *ui;
};

#endif // CHANGESHORTWINDOW_H

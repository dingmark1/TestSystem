#ifndef CHANGESINGLEWINDOW_H
#define CHANGESINGLEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ChangeSingleWindow;
}

class ChangeSingleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeSingleWindow(QWidget *parent = nullptr);
    void initData(int ID, const QString &question, const QStringList &options, int answer, const QString &subject);

    ~ChangeSingleWindow();

private slots:
    void on_upload_pushButton_clicked();

private:
    Ui::ChangeSingleWindow *ui;
};

#endif // CHANGESINGLEWINDOW_H

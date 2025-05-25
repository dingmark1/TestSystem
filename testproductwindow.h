#ifndef TESTPRODUCTWINDOW_H
#define TESTPRODUCTWINDOW_H

#include <QMainWindow>

namespace Ui {
class TestProductWindow;
}

class TestProductWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestProductWindow(QWidget *parent = nullptr);
    ~TestProductWindow();

private slots:
    void on_query_pushButton_clicked();

    void handleQueryFinished(bool success, const QString &message, const QJsonArray &questionList);

    void on_add_pushButton_2_clicked();

    void on_finish_pushButton_clicked();

    void on_delete_pushButton_3_clicked();

    void handleAddTestFinished(bool success, const QString &message);

private:
    Ui::TestProductWindow *ui;
};

#endif // TESTPRODUCTWINDOW_H

#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QMainWindow>

namespace Ui {
class TestView;
}

class TestView : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestView(QWidget *parent = nullptr);
    ~TestView();

private slots:
    void on_query_pushButton_clicked();

    void on_view_pushButton_2_clicked();

    void on_finish_pushButton_clicked();

    void on_download_pushButton_clicked();

private:
    Ui::TestView *ui;
};

#endif // TESTVIEW_H

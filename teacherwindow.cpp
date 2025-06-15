#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include "uploadquestionwindow.h"
#include "questionmanagewindow.h"
#include "testview.h"

TeacherWindow::TeacherWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);
    // setWindowFlags(Qt::Window);
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}




void TeacherWindow::on_manage_pushButton_2_clicked()
{
    // 跳转至题目管理页面
    QuestionManageWindow *questionmanagewindow = new QuestionManageWindow(this);
    questionmanagewindow -> show();
}


void TeacherWindow::on_upload_pushButton_clicked()
{
    // 跳转至题目上传选择界面
    UploadQuestionWindow *uploadquestionwindow = new UploadQuestionWindow(this);
    uploadquestionwindow -> show();
    // this -> hide();
}


void TeacherWindow::on_pushButton_clicked()
{
    // 跳转到试卷查看界面
    TestView *testview = new TestView(this);
    testview -> show();
}


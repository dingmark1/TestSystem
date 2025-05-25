#include "uploadquestionwindow.h"
#include "ui_uploadquestionwindow.h"
#include "singleselectwindow.h"
#include "mulselectwindow.h"
#include "judgewindow.h"
#include "shortanswerwindow.h"

UploadQuestionWindow::UploadQuestionWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UploadQuestionWindow)
{
    ui->setupUi(this);
}

UploadQuestionWindow::~UploadQuestionWindow()
{
    delete ui;
}

void UploadQuestionWindow::on_singleselect_pushButton_clicked()
{
    // 跳转到单选题上传界面
    SingleSelectWindow *singleselectwindow = new SingleSelectWindow(this);
    singleselectwindow -> show();
}


void UploadQuestionWindow::on_mulselect_pushButton_2_clicked()
{
    // 跳转到多选题界面
    MulSelectWindow *mulselectwindow = new MulSelectWindow(this);
    mulselectwindow -> show();
}


void UploadQuestionWindow::on_judge_pushButton_3_clicked()
{
    // 判断题
    JudgeWindow *judgewindow = new JudgeWindow(this);
    judgewindow -> show();
}


void UploadQuestionWindow::on_short_pushButton_4_clicked()
{
    // 简答题
    ShortAnswerWindow *shortanswerwindow = new ShortAnswerWindow(this);
    shortanswerwindow -> show();
}


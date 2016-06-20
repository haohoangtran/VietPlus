#include "review.h"
#include "ui_review.h"
#include"mainwindow.h"
#include<QString>
#include<QDebug>

ReView::ReView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReView)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Xem trước"));



}

ReView::~ReView()
{
    delete ui;
}

void ReView::on_pushButton_clicked()
{
    this->close();
}
void ReView::datxauvao(QString &s)
{
    ui->textBrowser->setText(s);
}



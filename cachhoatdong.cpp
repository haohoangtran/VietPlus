#include "cachhoatdong.h"
#include "ui_cachhoatdong.h"

Cachhoatdong::Cachhoatdong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cachhoatdong)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Cách hoạt động của phần mềm"));
}

Cachhoatdong::~Cachhoatdong()
{
    delete ui;
}

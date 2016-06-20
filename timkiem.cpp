#include "timkiem.h"
#include "ui_timkiem.h"

Timkiem::Timkiem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timkiem)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Tìm kiếm"));
}

Timkiem::~Timkiem()
{
    delete ui;
}
QString Timkiem::timkiem() const
{
    return ui->lineEditTimkiem->text();
}

void Timkiem::on_pushButtonTimkiem_clicked()
{
    accept();
    this->close();
}

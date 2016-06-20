#include "thaythe.h"
#include "ui_thaythe.h"

Thaythe::Thaythe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Thaythe)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Thay thế"));
}

Thaythe::~Thaythe()
{
    delete ui;
}
QString Thaythe::bithaythe() const
{
    return ui->lineEditbithay->text();
}
QString Thaythe::sethaythe() const
{
    return ui->lineEditSethay->text();
}

void Thaythe::on_pushButtonXn_clicked()
{
    accept();
    this->close();
}

void Thaythe::on_pushButtonhuy_clicked()
{
    this->close();
}

#include "duan.h"
#include "ui_duan.h"

Duan::Duan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Duan)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Về dự án VietPlus"));
}

Duan::~Duan()
{
    delete ui;

}

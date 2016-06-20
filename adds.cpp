#include "adds.h"
#include "ui_adds.h"
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QTextStream>
#include<QFile>
#include<QFileDialog>

Adds::Adds(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Adds)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromUtf8("Thêm mới"));
}

Adds::~Adds()
{
    delete ui;
}

void Adds::on_pushButtonThem_clicked()
{
    QString viettat=ui->lineEditViettat->text();
    accept();
    QString vietchuan=ui->lineEditVietchuan->text();
    if(viettat.isEmpty()||vietchuan.isEmpty())
        QMessageBox::critical(this,QString::fromUtf8("Lỗi"),QString::fromUtf8("Xin nhập lại!"));
    else{
        qDebug()<<viettat<<" "<<vietchuan;
    QFile file("tuviettat.txt");
    file.open(QIODevice ::ReadWrite);
    QString s;
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    s=textStream.readAll();
    file.close();
    s.append(viettat);s.append("=");s.append(vietchuan);s.append(";");
    QFile f("tuviettat.txt");
    f.open(QIODevice :: ReadWrite);
            QTextStream str(&f);
            str.setCodec("UTF-8");
            str<<s;
            str.flush();
            f.close();}
    this->close();

}

void Adds::on_pushButtonHuy_clicked()
{
    this->close();
}
QString Adds::viettat() const
{
    return ui->lineEditViettat->text();
}
QString Adds::vietchuan() const
{
    return ui->lineEditVietchuan->text();
}

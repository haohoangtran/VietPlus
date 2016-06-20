#include "botuviettat.h"
#include "ui_botuviettat.h"
#include"adds.h"
#include<QFile>
#include<QFileDialog>
#include<QString>
#include<QMessageBox>
#include<QStringList>
#include<QTextStream>
#include<QDebug>

Botuviettat::Botuviettat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Botuviettat)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromUtf8("Bộ từ viết tắt"));
    QFile file("tuviettat.txt");
    file.open(QIODevice ::ReadOnly);
    QString s,a,temp,xau;
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    s = textStream.readAll();
    QStringList mgiua,vietTat,vietChuan;
    mgiua = s.split(";",QString::SkipEmptyParts);

    for(int k=0;k<mgiua.size();k++)

    for(int i=0;i<mgiua.at(k).size();i++)
    {
        if(mgiua.at(k)[i]=='='){

            for(int j=0;j<i;j++)
                a.append(mgiua.at(k)[j]);
            vietTat<<a;//"d","dc"
            a="";temp=mgiua.at(k);
         temp.remove(0,i+1);
         vietChuan<<temp;

         temp="";
        }
    }for(int i=0;i<vietTat.size();i++)
    qDebug()<<vietTat.at(i)<<vietChuan.at(i);
//ui->textEdit->setText(s);
    int vitri;
    QStringList danhSachCot;


    danhSachCot.clear();
    vitri=s.indexOf(xau);
    qDebug()<<vitri;
    int k=0;
    ui->tableWidget->setColumnCount(2);
    danhSachCot<<QString::fromUtf8("Từ viết tắt")<<QString::fromUtf8("Từ viết chuẩn");
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setHorizontalHeaderLabels(danhSachCot);
    for(int i=1;i<=vietTat.size();i++)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        xau=vietTat.at(i-1);
        ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(xau));
        k++;
}
    for(int i=1;i<=vietChuan.size();i++)
    {
        xau=vietChuan.at(i-1);
        ui->tableWidget->setItem(i-1,1,new QTableWidgetItem(xau));
        k++;
    }
    ui->tableWidget->setColumnWidth(0,300);
    ui->tableWidget->setColumnWidth(1,300);



//table gợi ý.
}


Botuviettat::~Botuviettat()
{
    delete ui;
}

void Botuviettat::on_pushButtonThem_clicked()
{   int res;
    Adds ad;
    QString tat,chuan;
    res=ad.exec();
    if(res==Adds::Rejected)
        return;
    tat=ad.viettat();
    chuan=ad.vietchuan();
    if(tat.isEmpty() || chuan.isEmpty())
        QMessageBox::warning(this,QString::fromUtf8("Lỗi"),QString::fromUtf8("Bạn nhập thiếu từ viết tắt hoặc viết chuẩn"));
    else
    {
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(tat));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(chuan));
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    }


}
QStringList Botuviettat::tuviettat()
{
    QFile file("tuviettat.txt");
    file.open(QIODevice ::ReadOnly);
    QString s,a,temp,xau;
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    s = textStream.readAll();
    QStringList mgiua,vietTat,vietChuan;
    mgiua = s.split(";",QString::SkipEmptyParts);

    for(int k=0;k<mgiua.size();k++)

    for(int i=0;i<mgiua.at(k).size();i++)
    {
        if(mgiua.at(k)[i]=='='){

            for(int j=0;j<i;j++)
                a.append(mgiua.at(k)[j]);
            vietTat<<a;//"d","dc"
            a="";temp=mgiua.at(k);
         temp.remove(0,i+1);
         vietChuan<<temp;

         temp="";
        }
    }
    return vietTat;
}
QStringList Botuviettat::tuvietchuan()
{
    QFile file("tuviettat.txt");
    file.open(QIODevice ::ReadOnly);
    QString s,a,temp,xau;
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    s = textStream.readAll();
    QStringList mgiua,vietTat,vietChuan;
    mgiua = s.split(";",QString::SkipEmptyParts);

    for(int k=0;k<mgiua.size();k++)

    for(int i=0;i<mgiua.at(k).size();i++)
    {
        if(mgiua.at(k)[i]=='='){

            for(int j=0;j<i;j++)
                a.append(mgiua.at(k)[j]);
            vietTat<<a;
            a="";temp=mgiua.at(k);
         temp.remove(0,i+1);
         vietChuan<<temp;

         temp="";
        }
    }
    return vietChuan;
}

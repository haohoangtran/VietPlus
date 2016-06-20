#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextCharFormat>
#include"settings.h"
#include"aboutus.h"
#include"cachhoatdong.h"
#include"timkiem.h"
#include<review.h>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFileInfo>
#include <QFontDatabase>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextCodec>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QPrintPreviewDialog>
#include<QMessageBox>
#include<QStringList>
#include<QString>
#include<QDebug>
#include<QTextStream>
#include<QCloseEvent>
#include<QDebug>
#include<QChar>
#include<QFile>
#include<QFileDialog>
#include"botuviettat.h"
#include"adds.h"
#include"thaythe.h"
#include<duan.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->close();
    setWindowTitle(QString::fromUtf8("VietPlus v1.0.0"));
    ui->textBrowser->setText(QString::fromUtf8("<center>Phần mềm chuẩn hoá văn bản <b>VietPlus</b> v1.0.0</center>"));
    ui->actionNew->setShortcut(Qt::CTRL + Qt::Key_N);
    ui->actionOpen->setShortcut(Qt::CTRL + Qt::Key_O);
    ui->actionFind->setShortcut(Qt::CTRL + Qt::Key_F);
    ui->actionSave->setShortcut(Qt::CTRL + Qt::Key_S);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionB->setShortcut(Qt::CTRL + Qt::Key_B);
    ui->actionB->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    ui->actionB->setFont(bold);
    connect(ui->actionB, SIGNAL(triggered()), this, SLOT(textBold()));

    ui->actionB->setCheckable(true);


    ui->actionIn_nghi_ng->setPriority(QAction::LowPriority);
    ui->actionIn_nghi_ng->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    ui->actionIn_nghi_ng->setFont(italic);
    connect(ui->actionIn_nghi_ng, SIGNAL(triggered()), this, SLOT(textItalic()));

    ui->actionIn_nghi_ng->setCheckable(true);


    ui->actionG_ch_ch_n->setShortcut(Qt::CTRL + Qt::Key_U);
    ui->actionG_ch_ch_n->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    ui->actionG_ch_ch_n->setFont(underline);
    connect(ui->actionG_ch_ch_n, SIGNAL(triggered()), this, SLOT(textUnderline()));

    ui->actionG_ch_ch_n->setCheckable(true);
    ui->textEdit->setFocus();


    fontChanged(ui->textEdit->font());
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        ui->comboBoxFont->addItem(QString::number(size));

    connect(ui->comboBoxFont, SIGNAL(activated(QString)),
            this, SLOT(textSize(QString)));
    ui->comboBoxFont->setCurrentIndex(ui->comboBoxFont->findText(QString::number(QApplication::font()
                                                                   .pointSize())));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSetting_triggered()
{   int res,daucach;
    Settings settings;
    settings.setModal(true);
    res=settings.exec();
    if(res==Settings::Rejected)
        return;
    daucach=settings.sodaucach();

    qDebug()<<daucach;

}
void MainWindow::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        thayDoiDinhDangText(fmt);
    }
}

void MainWindow::on_actionVersion_triggered()
{
    QMessageBox::information(this,QString::fromUtf8("Phiên bản"),QString::fromUtf8("Phần mềm chuẩn hoá văn bản <b>VietPlus</b> v1.0.0"));
}

void MainWindow::on_actionAbouUs_triggered()
{
    AboutUs me;
    me.setModal(true);
    me.exec();
}

void MainWindow::on_actioWork_triggered()
{
    Cachhoatdong cachhd;
    cachhd.setModal(true);
    cachhd.exec();

}

void MainWindow::on_actionNew_triggered()
{
    ui->textBrowser->close();
    ui->textEdit->show();
    if(ui->textEdit->toPlainText().isEmpty())

    ui->textEdit->clear();
    else
        if(QMessageBox::information(this,QString::fromUtf8("Lưu"),QString::fromUtf8("Bạn có muốn lưu lại trước khi tạo mới?"),QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok)
    {on_actionSave_triggered();
            ui->textEdit->clear();}
    else
        ui->textEdit->clear();
}

void MainWindow::on_actionSave_triggered()
{
    QString vanbantxt;

    vanbantxt=ui->textEdit->toPlainText();


    if(vanbantxt.isEmpty())
        QMessageBox::critical(this,QString::fromUtf8("Trống!"),QString::fromUtf8("Văn bản trống không thể lưu!"));
    else
    {
    QString filename=QFileDialog::getSaveFileName(this,tr("Luu file"),QString(),
                                                 tr("Text file (*.txt)"));

    if(!filename.isEmpty())
    {   QFile file(filename);
        if(!file.open(QIODevice::WriteOnly))
        {
        QMessageBox::critical(this,QString::fromUtf8("Lỗi"),QString::fromUtf8("Tên không được để trống!"));
        }
        else
        {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        stream<<ui->textEdit->toPlainText();
        stream.flush();
        file.close();

        }
    }
}
}

void MainWindow::on_actionOpen_triggered()
{
    QString name=QFileDialog::getOpenFileName(this,QString::fromUtf8("Mở File"),"","Text File (*.txt)");
    QFile file(name);
    file.open(QIODevice::ReadWrite);
    QString str;
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    str=textStream.readAll();
    ui->textBrowser->close();
    ui->textEdit->show();
    ui->textEdit->setText(str);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    QString pd=ui->textEdit->toPlainText();
    if(!pd.isEmpty())
    if(QMessageBox::critical(this, QString::fromUtf8("Lưu?"),QString::fromUtf8("Bạn có muốn lưu lại văn bản trước khi thoát?"),QMessageBox::Ok|QMessageBox::Cancel)==QMessageBox::Ok)
       on_actionSave_triggered();
    event->accept();
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionFind_triggered()
{
    QString tim,xautimkiem;
        int res,vitritimkiem=-1,k=0;
        Timkiem find;
        find.setModal(true);
        res= find.exec();
        if(res==QDialog::Rejected)
            return;
           tim= find.timkiem();
           if(tim.isEmpty())
               QMessageBox::critical(this,QString::fromUtf8("Lỗi"),QString::fromUtf8("Bạn không được để trống trường này!"),QMessageBox::Ok);
           else
        qDebug()<<tim;

           //tìm tiếp.

       xautimkiem=ui->textEdit->toPlainText();ui->textEdit->setText(xautimkiem);
       vitritimkiem=xautimkiem.indexOf(tim,k);
       if(vitritimkiem==-1)
        QMessageBox::information(this,QString::fromUtf8("Không tìm thấy"),QString::fromUtf8("Từ bạn tìm không tồn tại!"));
       else
       {
           //xautimkiem.replace(vitritimkiem,tim.size(),QString::fromUtf8("<font color=\"red\">%1</font>").arg(tim));
           xautimkiem.remove(vitritimkiem,tim.size());
           xautimkiem.insert(vitritimkiem,QString::fromUtf8("<font color=\"red\">%1</font>").arg(tim));
       }
       k++;
       ui->textEdit->setText(xautimkiem);
}
void MainWindow::chuanhoavanban(QString &s)
{
    s[0]=s.data()[0].toUpper();

    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]==' '))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }


    //xoa chi de lai 1 dau ? neu co >2 dau
    for(int i=0;i<s.size();i++)
            if((s[i]=='?')&&(s[i+1]=='?'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }

    //xoa chi de lai 1 dau , neu co >2 dau
    for(int i=0;i<s.size();i++)
            if((s[i]==',')&&(s[i+1]==','))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xoa chi de lai 1 dau : neu co >2 daufor(int i=0;i<n;i++)
    for(int i=0;i<s.size();i++)
            if((s[i]==':')&&(s[i+1]==':'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xoa chi de lai 1 dau ; neu co >2 dau
    for(int i=0;i<s.size();i++)
            if((s[i]==';')&&(s[i+1]==';'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xóa chỉ để lại 1 dấu enter nếu có >2 dấu
    for(int i=0;i<s.size();i++)
            if((s[i]=='\n')&&(s[i+1]=='\n'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }

    //code xoá chỉ để lại 3 dấu chấm gần nhau
    for(int i=0;i<s.size();i++)
            if((s[i]=='.')&&(s[i+1]=='.')&&(s[i+2]=='.')&&(s[i+3]=='.'))
              {
                for(int j=i+2; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }

    //code mẫu.
    //code xóa chi de lai 1 dau !
    for(int i=0;i<s.size();i++)
            if((s[i]=='!')&&(s[i+1]=='!'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }


    //code xoa dau cach truoc dau .
    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]=='.'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xoá dấu cách trước dấu ,
    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]==','))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xoá dấu cách trước dấu !
    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]=='!'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xoá dấu cách trước dấu ?
    //
    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]=='?'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }
    //xoá dấu cách trước dấu ;
    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]==';'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }

    //xoá dấu cách trước dấu :
    for(int i=0;i<s.size();i++)
            if((s[i]==' ')&&(s[i+1]==':'))
              {
                for(int j=i; j<s.size()-1;j++)
                  s[j]=s[j+1];
                i--;
                s.remove(s.size()-1,1);
              }




    //thêm dấu chấm vào cuối xâu nếu cuối chưa có dấu . hoặc !
       //thêm push bottun vào để thụt đầu dòng
       //thêm check box cho linh hoạt lựa chọn người dùng
       //bỏ gạch \n,giữa 2 đoạn văn enter bao nhiêu lần,đoạn văn lùi vào bao nhiêu khoảng trắng
       //thay thế các từ viết tắt dc= được
       //2 từ viết hoa thay từ sau = thường.
    //them dau cach sau dau .
    // xem lại đoạn văn bản lùi đầu dòng .....
      //bẳng băm
      //tránh mã cứng!
      //dùng 2 mảng bằng txt sửa ngôn ngữ chát
     //thêm thanh công cụ GUI;

//thay dấu nháy kép " " bằng dấu “”

    //them dau cach sau dau cham .
    for(int i=0;i<s.size();i++)
        for(int i=0;i<s.size();i++)
    {
        if(s[i]=='.'&&s[i+1]!=' '&&s[i+1]!='.'&&s[i+1]!='\0'&&s[i+1]!='\n')
            s.insert(i+1," ");
    }
    //them dau cach sau dau ,
    for(int i=0;i<s.size();i++)
        for(int i=0;i<s.size();i++)
    {
        if(s[i]==','&&s[i+1]!=' ')
            s.insert(i+1," ");
    }
    //them dau cach sau dau !
        for(int i=0;i<s.size();i++)
            for(int i=0;i<s.size();i++)
        {
            if(s[i]=='!'&&s[i+1]!=' '&&(s[i+1]!='\0'&&s[i+1]!='\n'))
                s.insert(i+1," ");
        }
    //thm dau cach sau dau :
        for(int i=0;i<s.size();i++)
            for(int i=0;i<s.size();i++)
        {
            if(s[i]==':'&&s[i+1]!=' ')
                s.insert(i+1," ");
        }
    //them dau cach sau dau ;
        for(int i=0;i<s.size();i++)
            for(int i=0;i<s.size();i++)
        {
            if(s[i]==';'&&s[i+1]!=' ')
                s.insert(i+1," ");
        }
    //them dau cach sau dau ?
        for(int i=0;i<s.size();i++)
            for(int i=0;i<s.size();i++)
        {
            if(s[i]=='?'&&s[i+1]!=' '&&s[i+1]!='\0'&&s[i+1]!='\n')
                s.insert(i+1," ");
        }
        //xoá dấu cách trước dấu enter
        for(int i=0;i<s.size();i++)
                if((s[i]==' ')&&(s[i+1]=='\r')&&s[i+2]=='\n')
                  {
                    for(int j=i; j<s.size()-1;j++)
                      s[j]=s[j+1];
                    i--;
                    s.remove(s.size()-1,1);
                  }
   //thêm dấu cách trước dấu gạch ngang
        for(int i=0;i<s.size();i++)
            for(int i=0;i<s.size();i++)
            {
                if(s[i].isLower()&&s[i+1]=='-')
                    s.insert(i+1," ");
            }
   //thêm dấu cách sau dấu gạch ngang
        for(int i=0;i<s.size();i++)
            for(int i=0;i<s.size();i++)
        {
            if(s[i]=='-'&&s[i+1]!=' ')
                s.insert(i+1," ");
        }

        //code xoa dau cach sau enter
        for(int i=0;i<s.size();i++)
        {
            if(s[i]=='\n'&&s[i+1]==' ')
                s.remove(i+1);
        }
    //chu sau dau . phai viet hoa
            for(int i=0;i<s.size();i++)
            {
                if((s[i]=='.')&&(s[i+1]==' '))
                {QChar kytu=s[i+2];
                    s[i+2]=kytu.toUpper();
            }}
   //chu sau dau ! phai viet hoa
            for(int i=0;i<s.size();i++)
            {
                if((s[i]=='!')&&(s[i+1]==' '))
                {QChar kytu=s[i+2];
                    s[i+2]=kytu.toUpper();
            }}
   //chu sau dau ? phai viet hoa
            for(int i=0;i<s.size();i++)
            {
                if((s[i]=='?')&&(s[i+1]==' '))
                {QChar kytu=s[i+2];
                    s[i+2]=kytu.toUpper();
            }}
  //chu sau dau enter phai viet hoa
            for(int i=0;i<s.size();i++)
            {
                if((s[i]=='\n'))
                {QChar kytu=s[i+1];
                    s[i+1]=s.data()[i+1].toUpper();
                       s[i+1]= kytu.toUpper();}
            }
  // chữ sau dấu enter có một dấu cách phải viết hoa
                for(int i=0;i<s.size();i++)
                {
                    if((s[i]=='\n')&&(s[i+1]==' '))
                    {QChar kytu=s[i+2];
                        s[i+2]=s.data()[i+2].toUpper();
                           s[i+2]= kytu.toUpper();}
                }
  // chữ sau dấu gạch ngang phải viết hoa
            for(int i=0;i<s.size();i++)
            {
                if((s[i]=='\n')&&(s[i+1]=='-'&&s[i+2]==' '))
                {QChar kytu=s[i+3];
                    s[i+3]=kytu.toUpper();
            }}
  //2 chu viet hoa dung canh nhau chuyen thanh chu dau viet hoa
            for(int i=0;i<s.size();i++)
            {
              s[i+1]==s[i+1].toLower();
                if((s[i]>='A')&&(s[i]<='Z')&&(s[i+1]>='A')&&(s[i+1]<='Z')&&(s[i+2]>='a')&&(s[i+2]<='z'))
                {
                  QChar kytu1,kytu2,kytu3;
                  kytu1=s[i];
                  kytu2=s[i+1];
                  kytu3=s[i+2];

                  if(kytu1.isUpper()&&kytu2.isUpper()&&kytu3.isLower())
                     s[i+1]=kytu2.toLower();

                }

            }
           for(int i=0;i<s.size();i++)
            { if(s[i].isUpper()&&s[i+1].isUpper()&&s[i+2].isLower())
                    s[i+1]=s[i+1].toLower();}
//chữ đầu là chữ thường thì chữ liền sau cũng phải là chữ thường
           for(int i=0;i<s.size();i++)
           {
               if(s[i].isLower()&&s[i+1].isUpper())
                   s[i+1]=s[i+1].toLower();
           }

           for(int i=0;i<s.size();i++)
           {
       //sau dấu , là chữ thường
               if(s[i]==','&&s[i+1]==' '&&s[i+2].isUpper())
                   s[i+2]=s[i+2].toLower();
      //sau dấu ; là chữ thường
               if(s[i]==';'&&s[i+1]==' '&&s[i+2].isUpper())
                   s[i+2]=s[i+2].toLower();
      //sau dấu : là chữ thường
               if(s[i]==':'&&s[i+1]==' '&&s[i+2].isUpper())
                   s[i+2]=s[i+2].toLower();
           }


//phần về các từ viết tắt trong văn bản





 //thêm dấu chấm vào cuối

         if(s[s.size()-1]!='.'&&s[s.size()-1]!='!'&&s[s.size()-1]!='?')
          s.push_back('.');
}

void MainWindow::on_actionChuanHoaVanBan_triggered()
{
    QString xaucanchuanhoa=ui->textEdit->toPlainText();
    if(xaucanchuanhoa.isEmpty())
        QMessageBox::critical(this,QString::fromUtf8("Văn bản trống!"),QString::fromUtf8("Văn bản bạn nhập không được để trống!"));
    else
    {int daucach;
            Settings settings;

            daucach=settings.sodaucach();
        chuanhoavanban(xaucanchuanhoa);
        if(thaytheviettat()==true)
            botuviettat(xaucanchuanhoa);
        if(tuthemdaucham()==true)
           tudongthemdaucham(xaucanchuanhoa);
        if(sualoikieugo()==true)
            tudongsualoikieugo(xaucanchuanhoa);
        if(daucach!=-1)
        {xaucanchuanhoa.insert(0," ");
        for(int i=0;i<daucach;i++)
        {   xaucanchuanhoa.insert(0," ");
            luidaudong(xaucanchuanhoa);
        }
        //xaucanchuanhoa.insert(0," ");
        }
        else
            xaucanchuanhoa.insert(0," ");
            luidaudong(xaucanchuanhoa);



    ui->textEdit->setText(xaucanchuanhoa);
    }

}
void MainWindow::luidaudong(QString &xau)
{
    for(int i=0;i<xau.size();i++)
    {
        if(xau[i]=='\n')
            xau.insert(i+1," ");
    }
}


void MainWindow::on_actionBoTuVietTat_triggered()
{
   Botuviettat bt;
   bt.setModal(true);
   bt.exec();
}
void MainWindow::botuviettat(QString &str)
{
    Botuviettat bt;
    QStringList btviettat,btvietchuan;
    btviettat=bt.tuviettat();
    btvietchuan=bt.tuvietchuan();
    for(int i=0;i<btviettat.size();i++)
        str.replace(btviettat.at(i),btvietchuan.at(i));
}

void MainWindow::on_actionReplace_triggered()
{
    Thaythe tt;int res;
    res=tt.exec();
    if(res==Thaythe::Rejected)
        return;
    QString canthay,sethay;
    canthay=tt.bithaythe();
    sethay=tt.sethaythe();
    if(canthay.isEmpty() || sethay.isEmpty())
     QMessageBox::information(this,QString::fromUtf8("Lỗi!"),QString::fromUtf8("Bạn không nhập từ bị thay hoặc sẽ thay!"));
    else
    {
        QString str=ui->textEdit->toPlainText();
        str.replace(canthay,sethay);
        ui->textEdit->setText(str);

    }
}

void MainWindow::on_actionVanBanSauChinhSua_triggered()
{
    QString sd=ui->textEdit->toPlainText();
    if(sd.isEmpty())
    {
        QMessageBox::information(this,QString::fromUtf8("Lỗi"),QString::fromUtf8("Văn bản để xem trước trống!"));

    }
    else
    {
       chuanhoavanban(sd);
       luidaudong(sd);
       QMessageBox::information(this,QString::fromUtf8("Xem trước"),sd);
    }

}


void MainWindow::on_actionAboutProject_triggered()
{
    Duan da;
    da.exec();
}

bool MainWindow::tuthemdaucham()
{
    Settings st;
    return st.tudongthemdaucham();
}
bool MainWindow::thaytheviettat()
{
    Settings st;
    return st.tudongthaythetuviettat();
}
bool MainWindow::sualoikieugo()
{
    Settings st;
    return st.tudongsualoikieugo();
}
void MainWindow::tudongsualoikieugo(QString &s)
{
    for(int i=0;i<s.size();i++)
    {
//chuyển thành â hoặc Â.
        if(s[i]=='a'&&s[i+1]=='a')
            s.replace(i,2,L'â');
        if(s[i]=='A'&&(s[i+1]=='A'||s[i+1]=='a'))
            s.replace(i,2,L'Â');

//chuyển chữ dd thành chữ đ
        if(s[i]=='d'&&s[i+1]=='d')
            s.replace(i,2,L'đ');
        if(s[i]=='D'&&(s[i+1]=='d'||s[i+1]=='D'))
            s.replace(i,2,L'Đ');
//chuyển ee thành ê
        if(s[i]=='e'&&s[i+1]=='e')
            s.replace(i,2,L'ê');
        if(s[i]=='E'&&(s[i+1]=='e'||s[i+1]=='E'))
            s.replace(i,2,L'Ê');
//chuyển oo thành ô
        if(s[i].isLower()&&s[i+1]=='o'&&(s[i+2]=='o'))
            s.replace(i+1,2,L'ô');
        if(s[i]=='O'&&(s[i+1]=='o'||s[i+1]=='O'))
            s.replace(i,2,L'Ô');

//chuyển aw thành ă
        if(s[i]=='a'&&s[i+1]=='w')
            s.replace(i,2,L'ă');
        if(s[i]=='A'&&(s[i+1]=='w'||s[i+1]=='W'))
            s.replace(i,2,L'Ă');
//chuyển uw thành ư
        if(s[i]=='u'&&s[i+1]=='w')
            s.replace(i,2,L'ư');
        if(s[i]=='U'&&(s[i+1]=='w'||s[i+1]=='W'))
            s.replace(i,2,L'Ư');
//chuyển ow thành ơ
        if(s[i]=='o'&&s[i+1]=='w')
            s.replace(i,2,L'ơ');
        if(s[i]=='O'&&(s[i+1]=='w'||s[i+1]=='W'))
            s.replace(i,2,L'Ơ');
//trường hợp chữ a

        if(s[i]=='a'&&s[i+1]=='s')
            s.replace(i,2,L'á');
        if(s[i]=='a'&&s[i+1]=='f')
            s.replace(i,2,L'à');
        if(s[i]=='a'&&s[i+1]=='j')
            s.replace(i,2,L'ạ');
        if(s[i]=='a'&&s[i+1]=='x')
            s.replace(i,2,L'ã');
        if(s[i]=='a'&&s[i+1]=='r')
            s.replace(i,2,L'ả');
   //trường hợp chữ A
        if(s[i]=='A'&&s[i+1]=='s')
            s.replace(i,2,L'Á');
        if(s[i]=='A'&&s[i+1]=='f')
            s.replace(i,2,L'À');
        if(s[i]=='A'&&s[i+1]=='j')
            s.replace(i,2,L'Ạ');
        if(s[i]=='A'&&s[i+1]=='x')
            s.replace(i,2,L'Ã');
        if(s[i]=='A'&&s[i+1]=='r')
            s.replace(i,2,L'Ả');
        // sau chữ A là ký tự thể hiện dấu viết hoa
        if(s[i]=='A'&&s[i+1]=='S')
            s.replace(i,2,L'Á');
        if(s[i]=='A'&&s[i+1]=='F')
            s.replace(i,2,L'À');
        if(s[i]=='A'&&s[i+1]=='J')
            s.replace(i,2,L'Ạ');
        if(s[i]=='A'&&s[i+1]=='X')
            s.replace(i,2,L'Ã');
        if(s[i]=='A'&&s[i+1]=='R')
            s.replace(i,2,L'Ả');
//trường hợp chữ ă

        if(s[i]==L'ă'&&s[i+1]=='s')
            s.replace(i,2,L'ắ');
        if(s[i]==L'ă'&&s[i+1]=='f')
            s.replace(i,2,L'ằ');
        if(s[i]==L'ă'&&s[i+1]=='j')
            s.replace(i,2,L'ặ');
        if(s[i]==L'ă'&&s[i+1]=='x')
            s.replace(i,2,L'ẵ');
        if(s[i]==L'ă'&&s[i+1]=='r')
            s.replace(i,2,L'ẳ');
//trường hợp chữ Ă
        if(s[i]==L'Ă'&&s[i+1]=='s')
            s.replace(i,2,L'Ắ');
        if(s[i]==L'Ă'&&s[i+1]=='f')
            s.replace(i,2,L'Ằ');
        if(s[i]==L'Ă'&&s[i+1]=='j')
            s.replace(i,2,L'Ặ');
        if(s[i]==L'Ă'&&s[i+1]=='x')
            s.replace(i,2,L'Ẵ');
        if(s[i]==L'Ă'&&s[i+1]=='r')
            s.replace(i,2,L'Ẳ');
        // sau chữ Ă là ký tự thể hiện dấu viết hoa
        if(s[i]==L'Ă'&&s[i+1]=='S')
            s.replace(i,2,L'Ắ');
        if(s[i]==L'Ă'&&s[i+1]=='F')
            s.replace(i,2,L'Ằ');
        if(s[i]==L'Ă'&&s[i+1]=='J')
            s.replace(i,2,L'Ặ');
        if(s[i]==L'Ă'&&s[i+1]=='X')
            s.replace(i,2,L'Ẵ');
        if(s[i]==L'Ă'&&s[i+1]=='R')
            s.replace(i,2,L'Ẳ');
//trường hợp chữ â

        if(s[i]==L'â'&&s[i+1]=='s')
            s.replace(i,2,L'ấ');
        if(s[i]==L'â'&&s[i+1]=='f')
            s.replace(i,2,L'ầ');
        if(s[i]==L'â'&&s[i+1]=='j')
            s.replace(i,2,L'ậ');
        if(s[i]==L'â'&&s[i+1]=='x')
            s.replace(i,2,L'ẫ');
        if(s[i]==L'â'&&s[i+1]=='r')
            s.replace(i,2,L'ẩ');
//trường hợp chữ Â
        if(s[i]==L'Â'&&s[i+1]=='s')
            s.replace(i,2,L'Ấ');
        if(s[i]==L'Â'&&s[i+1]=='f')
            s.replace(i,2,L'Ầ');
        if(s[i]==L'Â'&&s[i+1]=='j')
            s.replace(i,2,L'Ậ');
        if(s[i]==L'Â'&&s[i+1]=='x')
            s.replace(i,2,L'Ẫ');
        if(s[i]==L'Â'&&s[i+1]=='r')
            s.replace(i,2,L'Ẩ');
//sau chữ Â là ký tự thể hiện dấu viết hoa
        if(s[i]==L'Â'&&s[i+1]=='S')
            s.replace(i,2,L'Ấ');
        if(s[i]==L'Â'&&s[i+1]=='F')
            s.replace(i,2,L'Ầ');
        if(s[i]==L'Â'&&s[i+1]=='J')
            s.replace(i,2,L'Ậ');
        if(s[i]==L'Â'&&s[i+1]=='X')
            s.replace(i,2,L'Ẫ');
        if(s[i]==L'Â'&&s[i+1]=='R')
            s.replace(i,2,L'Ẩ');
//trường hợp chữ e

        if(s[i]=='e'&&s[i+1]=='s')
            s.replace(i,2,L'é');
        if(s[i]=='e'&&s[i+1]=='f')
            s.replace(i,2,L'è');
        if(s[i]=='e'&&s[i+1]=='j')
            s.replace(i,2,L'ẹ');
        if(s[i]=='e'&&s[i+1]=='x')
            s.replace(i,2,L'ẽ');
        if(s[i]=='e'&&s[i+1]=='r')
            s.replace(i,2,L'ẻ');
//trường hợp chữ E
        if(s[i]=='E'&&s[i+1]=='s')
            s.replace(i,2,L'É');
        if(s[i]=='E'&&s[i+1]=='f')
            s.replace(i,2,L'È');
        if(s[i]=='E'&&s[i+1]=='j')
            s.replace(i,2,L'Ẹ');
        if(s[i]=='E'&&s[i+1]=='x')
            s.replace(i,2,L'Ẽ');
        if(s[i]=='E'&&s[i+1]=='r')
            s.replace(i,2,L'Ẻ');
//sau chữ E là các ký tự thể hiện dấu viết hoa
        if(s[i]=='E'&&s[i+1]=='S')
            s.replace(i,2,L'É');
        if(s[i]=='E'&&s[i+1]=='F')
            s.replace(i,2,L'È');
        if(s[i]=='E'&&s[i+1]=='J')
            s.replace(i,2,L'Ẹ');
        if(s[i]=='E'&&s[i+1]=='X')
            s.replace(i,2,L'Ẽ');
        if(s[i]=='E'&&s[i+1]=='R')
            s.replace(i,2,L'Ẻ');
//trường hợp chữ ê

                         if(s[i]==L'ê'&&s[i+1]=='s')
                             s.replace(i,2,L'ế');
                         if(s[i]==L'ê'&&s[i+1]=='f')
                             s.replace(i,2,L'ề');
                         if(s[i]==L'ê'&&s[i+1]=='j')
                             s.replace(i,2,L'ệ');
                         if(s[i]==L'ê'&&s[i+1]=='x')
                             s.replace(i,2,L'ễ');
                         if(s[i]==L'ê'&&s[i+1]=='r')
                             s.replace(i,2,L'ể');
       //trường hợp chữ Ê
                         if(s[i]==L'Ê'&&s[i+1]=='s')
                             s.replace(i,2,L'Ế');
                         if(s[i]==L'Ê'&&s[i+1]=='f')
                             s.replace(i,2,L'Ề');
                         if(s[i]==L'Ê'&&s[i+1]=='j')
                             s.replace(i,2,L'Ệ');
                         if(s[i]==L'Ê'&&s[i+1]=='x')
                             s.replace(i,2,L'Ễ');
                         if(s[i]==L'Ê'&&s[i+1]=='r')
                             s.replace(i,2,L'Ể');
       //sau Ê là các ký tự dấu viết hoa
                         if(s[i]==L'Ê'&&s[i+1]=='S')
                             s.replace(i,2,L'Ế');
                         if(s[i]==L'Ê'&&s[i+1]=='F')
                             s.replace(i,2,L'Ề');
                         if(s[i]==L'Ê'&&s[i+1]=='J')
                             s.replace(i,2,L'Ệ');
                         if(s[i]==L'Ê'&&s[i+1]=='X')
                             s.replace(i,2,L'Ễ');
                         if(s[i]==L'Ê'&&s[i+1]=='R')
                             s.replace(i,2,L'Ể');
       //trường hợp chữ i
                         if(s[i]=='i'&&s[i+1]=='s')
                             s.replace(i,2,L'í');
                         if(s[i]=='i'&&s[i+1]=='f')
                             s.replace(i,2,L'ì');
                         if(s[i]=='i'&&s[i+1]=='j')
                             s.replace(i,2,L'ị');
                         if(s[i]=='i'&&s[i+1]=='x')
                             s.replace(i,2,L'ĩ');
                         if(s[i]=='i'&&s[i+1]=='r')
                             s.replace(i,2,L'ỉ');
       //trường hợp chữ I
                         if(s[i]=='I'&&s[i+1]=='s')
                             s.replace(i,2,L'Í');
                         if(s[i]=='I'&&s[i+1]=='f')
                             s.replace(i,2,L'Ì');
                         if(s[i]=='I'&&s[i+1]=='j')
                             s.replace(i,2,L'Ị');
                         if(s[i]=='I'&&s[i+1]=='x')
                             s.replace(i,2,L'Ĩ');
                         if(s[i]=='I'&&s[i+1]=='r')
                             s.replace(i,2,L'Ỉ');
               //chữ I sau nó là các ký tự dấu viết hoa
                         if(s[i]=='I'&&s[i+1]=='S')
                             s.replace(i,2,L'Í');
                         if(s[i]=='I'&&s[i+1]=='F')
                             s.replace(i,2,L'Ì');
                         if(s[i]=='I'&&s[i+1]=='J')
                             s.replace(i,2,L'Ị');
                         if(s[i]=='I'&&s[i+1]=='X')
                             s.replace(i,2,L'Ĩ');
                         if(s[i]=='I'&&s[i+1]=='R')
                             s.replace(i,2,L'Ỉ');
       //trường hợp chữ o

                         if(s[i]=='o'&&s[i+1]=='s')
                             s.replace(i,2,L'ó');
                         if(s[i]=='o'&&s[i+1]=='f')
                             s.replace(i,2,L'ò');
                         if(s[i]=='o'&&s[i+1]=='j')
                             s.replace(i,2,L'ọ');
                         if(s[i]=='o'&&s[i+1]=='x')
                             s.replace(i,2,L'õ');
                         if(s[i]=='o'&&s[i+1]=='r')
                             s.replace(i,2,L'ỏ');

      //trường hợp chữ O(hoa)
                         if(s[i]=='O'&&s[i+1]=='s')
                             s.replace(i,2,L'Ó');
                         if(s[i]=='O'&&s[i+1]=='f')
                             s.replace(i,2,L'Ò');
                         if(s[i]=='O'&&s[i+1]=='j')
                             s.replace(i,2,L'Ọ');
                         if(s[i]=='O'&&s[i+1]=='x')
                             s.replace(i,2,L'Õ');
                         if(s[i]=='O'&&s[i+1]=='r')
                             s.replace(i,2,L'Ỏ');
                //chữ O sau nó là các ký tự dấu hoa
                         if(s[i]=='O'&&s[i+1]=='S')
                             s.replace(i,2,L'Ó');
                         if(s[i]=='O'&&s[i+1]=='F')
                             s.replace(i,2,L'Ò');
                         if(s[i]=='O'&&s[i+1]=='J')
                             s.replace(i,2,L'Ọ');
                         if(s[i]=='O'&&s[i+1]=='X')
                             s.replace(i,2,L'Õ');
                         if(s[i]=='O'&&s[i+1]=='R')
                             s.replace(i,2,L'Ỏ');
      //trường hợp chữ ô
                         if(s[i]==L'ô'&&s[i+1]=='s')
                             s.replace(i,2,L'ố');
                         if(s[i]==L'ô'&&s[i+1]=='f')
                             s.replace(i,2,L'ồ');
                         if(s[i]==L'ô'&&s[i+1]=='j')
                             s.replace(i,2,L'ộ');
                         if(s[i]==L'ô'&&s[i+1]=='x')
                             s.replace(i,2,L'ỗ');
                         if(s[i]==L'ô'&&s[i+1]=='r')
                             s.replace(i,2,L'ổ');
      //trường hợp chữ Ô
                         if(s[i]==L'Ô'&&s[i+1]=='s')
                             s.replace(i,2,L'Ố');
                         if(s[i]==L'Ô'&&s[i+1]=='f')
                             s.replace(i,2,L'Ồ');
                         if(s[i]==L'Ô'&&s[i+1]=='j')
                             s.replace(i,2,L'Ộ');
                         if(s[i]==L'Ô'&&s[i+1]=='x')
                             s.replace(i,2,L'Ỗ');
                         if(s[i]==L'Ô'&&s[i+1]=='r')
                             s.replace(i,2,L'Ổ');
              //chữ Ô sau nó là dấu viết hoa
                         if(s[i]==L'Ô'&&s[i+1]=='S')
                             s.replace(i,2,L'Ố');
                         if(s[i]==L'Ô'&&s[i+1]=='F')
                             s.replace(i,2,L'Ồ');
                         if(s[i]==L'Ô'&&s[i+1]=='J')
                             s.replace(i,2,L'Ộ');
                         if(s[i]==L'Ô'&&s[i+1]=='X')
                             s.replace(i,2,L'Ỗ');
                         if(s[i]==L'Ô'&&s[i+1]=='R')
                             s.replace(i,2,L'Ổ');
      //trường hợp chữ ơ
                         if(s[i]==L'ơ'&&s[i+1]=='s')
                             s.replace(i,2,L'ớ');
                         if(s[i]==L'ơ'&&s[i+1]=='f')
                             s.replace(i,2,L'ờ');
                         if(s[i]==L'ơ'&&s[i+1]=='j')
                             s.replace(i,2,L'ợ');
                         if(s[i]==L'ơ'&&s[i+1]=='x')
                             s.replace(i,2,L'ỡ');
                         if(s[i]==L'ơ'&&s[i+1]=='r')
                             s.replace(i,2,L'ở');
    //trường hợp chữ Ơ
                         if(s[i]==L'Ơ'&&s[i+1]=='s')
                             s.replace(i,2,L'Ớ');
                         if(s[i]==L'Ơ'&&s[i+1]=='f')
                             s.replace(i,2,L'Ờ');
                         if(s[i]==L'Ơ'&&s[i+1]=='j')
                             s.replace(i,2,L'Ợ');
                         if(s[i]==L'Ơ'&&s[i+1]=='x')
                             s.replace(i,2,L'Ỡ');
                         if(s[i]==L'Ơ'&&s[i+1]=='r')
                             s.replace(i,2,L'Ở');
              //chữ Ơ sau nó là dấu viết hoa
                         if(s[i]==L'Ơ'&&s[i+1]=='S')
                             s.replace(i,2,L'Ớ');
                         if(s[i]==L'Ơ'&&s[i+1]=='F')
                             s.replace(i,2,L'Ờ');
                         if(s[i]==L'Ơ'&&s[i+1]=='J')
                             s.replace(i,2,L'Ợ');
                         if(s[i]==L'Ơ'&&s[i+1]=='X')
                             s.replace(i,2,L'Ỡ');
                         if(s[i]==L'Ơ'&&s[i+1]=='R')
                             s.replace(i,2,L'Ở');
  //trường hợp chữ u
                         if(s[i]=='u'&&s[i+1]=='s')
                             s.replace(i,2,L'ú');
                         if(s[i]=='u'&&s[i+1]=='f')
                             s.replace(i,2,L'ù');
                         if(s[i]=='u'&&s[i+1]=='j')
                             s.replace(i,2,L'ụ');
                         if(s[i]=='u'&&s[i+1]=='x')
                             s.replace(i,2,L'ũ');
                         if(s[i]=='u'&&s[i+1]=='r')
                             s.replace(i,2,L'ủ');
  //trường hợp chữ U
                         if(s[i]=='U'&&s[i+1]=='s')
                             s.replace(i,2,L'Ú');
                         if(s[i]=='U'&&s[i+1]=='f')
                             s.replace(i,2,L'Ù');
                         if(s[i]=='U'&&s[i+1]=='j')
                             s.replace(i,2,L'Ụ');
                         if(s[i]=='U'&&s[i+1]=='x')
                             s.replace(i,2,L'Ũ');
                         if(s[i]=='U'&&s[i+1]=='r')
                             s.replace(i,2,L'Ủ');
           //sau U là các dấu viết hoa
                         if(s[i]=='U'&&s[i+1]=='S')
                             s.replace(i,2,L'Ú');
                         if(s[i]=='U'&&s[i+1]=='F')
                             s.replace(i,2,L'Ù');
                         if(s[i]=='U'&&s[i+1]=='J')
                             s.replace(i,2,L'Ụ');
                         if(s[i]=='U'&&s[i+1]=='X')
                             s.replace(i,2,L'Ũ');
                         if(s[i]=='U'&&s[i+1]=='R')
                             s.replace(i,2,L'Ủ');
  //trường hợp chữ ư
                         if(s[i]==L'ư'&&s[i+1]=='s')
                             s.replace(i,2,L'ứ');
                         if(s[i]==L'ư'&&s[i+1]=='f')
                             s.replace(i,2,L'ừ');
                         if(s[i]==L'ư'&&s[i+1]=='j')
                             s.replace(i,2,L'ự');
                         if(s[i]==L'ư'&&s[i+1]=='x')
                             s.replace(i,2,L'ữ');
                         if(s[i]==L'ư'&&s[i+1]=='r')
                             s.replace(i,2,L'ử');
  //trường hợp chữ Ư
                         if(s[i]==L'Ư'&&s[i+1]=='s')
                             s.replace(i,2,L'Ứ');
                         if(s[i]==L'Ư'&&s[i+1]=='f')
                             s.replace(i,2,L'Ừ');
                         if(s[i]==L'Ư'&&s[i+1]=='j')
                             s.replace(i,2,L'Ự');
                         if(s[i]==L'Ư'&&s[i+1]=='x')
                             s.replace(i,2,L'Ữ');
                         if(s[i]==L'Ư'&&s[i+1]=='r')
                             s.replace(i,2,L'Ử');
              //sau Ư là các dấu viết hoa
                         if(s[i]==L'Ư'&&s[i+1]=='S')
                             s.replace(i,2,L'Ứ');
                         if(s[i]==L'Ư'&&s[i+1]=='F')
                             s.replace(i,2,L'Ừ');
                         if(s[i]==L'Ư'&&s[i+1]=='J')
                             s.replace(i,2,L'Ự');
                         if(s[i]==L'Ư'&&s[i+1]=='X')
                             s.replace(i,2,L'Ữ');
                         if(s[i]==L'Ư'&&s[i+1]=='R')
                             s.replace(i,2,L'Ử');
  //trường hợp chữ y
                         if(s[i]=='y'&&s[i+1]=='s')
                             s.replace(i,2,L'ý');
                         if(s[i]=='y'&&s[i+1]=='f')
                             s.replace(i,2,L'ỳ');
                         if(s[i]=='y'&&s[i+1]=='j')
                             s.replace(i,2,L'ỵ');
                         if(s[i]=='y'&&s[i+1]=='x')
                             s.replace(i,2,L'ỹ');
                         if(s[i]=='y'&&s[i+1]=='r')
                             s.replace(i,2,L'ỷ');
 //trường hợp chữ Y
                         if(s[i]=='Y'&&s[i+1]=='s')
                             s.replace(i,2,L'Ý');
                         if(s[i]=='Y'&&s[i+1]=='f')
                             s.replace(i,2,L'Ỳ');
                         if(s[i]=='Y'&&s[i+1]=='j')
                             s.replace(i,2,L'Ỵ');
                         if(s[i]=='Y'&&s[i+1]=='x')
                             s.replace(i,2,L'Ỹ');
                         if(s[i]=='Y'&&s[i+1]=='r')
                             s.replace(i,2,L'Ỷ');
               //sau Y là các dấu viết hoa
                         if(s[i]=='Y'&&s[i+1]=='S')
                             s.replace(i,2,L'Ý');
                         if(s[i]=='Y'&&s[i+1]=='F')
                             s.replace(i,2,L'Ỳ');
                         if(s[i]=='Y'&&s[i+1]=='J')
                             s.replace(i,2,L'Ỵ');
                         if(s[i]=='Y'&&s[i+1]=='X')
                             s.replace(i,2,L'Ỹ');
                         if(s[i]=='Y'&&s[i+1]=='R')
                             s.replace(i,2,L'Ỷ');
    }
for(int i=0;i<s.size();i++)
{
//code chuyển chữ a  mà sau nó là các dấu  và w
   if(s[i]==L'á'&&s[i+1]=='w')
       s.replace(i,2,L'ắ');
   if(s[i]==L'à'&&s[i+1]=='w')
       s.replace(i,2,L'ằ');
   if(s[i]==L'ạ'&&s[i+1]=='w')
       s.replace(i,2,L'ặ');
   if(s[i]==L'ã'&&s[i+1]=='w')
       s.replace(i,2,L'ẵ');
   if(s[i]==L'ả'&&s[i+1]=='w')
       s.replace(i,2,L'ẳ');
//code chuyển chữ A mà sao nó là các dấu và w
   if(s[i]==L'Á'&&s[i+1]=='w')
       s.replace(i,2,L'Ắ');
   if(s[i]==L'À'&&s[i+1]=='w')
       s.replace(i,2,L'Ằ');
   if(s[i]==L'Ạ'&&s[i+1]=='w')
       s.replace(i,2,L'Ặ');
   if(s[i]==L'Ã'&&s[i+1]=='w')
       s.replace(i,2,L'Ẵ');
   if(s[i]==L'Ả'&&s[i+1]=='w')
       s.replace(i,2,L'Ẳ');
//code chuyển chữ A mà sau nó là các dấu và chữ W(hoa)
   if(s[i]==L'Á'&&s[i+1]=='W')
       s.replace(i,2,L'Ắ');
   if(s[i]==L'À'&&s[i+1]=='W')
       s.replace(i,2,L'Ằ');
   if(s[i]==L'Ạ'&&s[i+1]=='W')
       s.replace(i,2,L'Ặ');
   if(s[i]==L'Ã'&&s[i+1]=='W')
       s.replace(i,2,L'Ẵ');
   if(s[i]==L'Ả'&&s[i+1]=='W')
       s.replace(i,2,L'Ẳ');
//code chuyển chữ a mà sau nó là các dấu và a
   if(s[i]==L'á'&&s[i+1]=='a')
       s.replace(i,2,L'ấ');
   if(s[i]==L'à'&&s[i+1]=='a')
       s.replace(i,2,L'ầ');
   if(s[i]==L'ạ'&&s[i+1]=='a')
       s.replace(i,2,L'ậ');
   if(s[i]==L'ã'&&s[i+1]=='a')
       s.replace(i,2,L'ẫ');
   if(s[i]==L'ả'&&s[i+1]=='a')
       s.replace(i,2,L'ẩ');
//code chuyển chữ A mà sau nó là các dấu và a
   if(s[i]==L'Á'&&s[i+1]=='a')
       s.replace(i,2,L'Ấ');
   if(s[i]==L'À'&&s[i+1]=='a')
       s.replace(i,2,L'Ầ');
   if(s[i]==L'Ạ'&&s[i+1]=='a')
       s.replace(i,2,L'Ậ');
   if(s[i]==L'Ã'&&s[i+1]=='a')
       s.replace(i,2,L'Ẫ');
   if(s[i]==L'Ả'&&s[i+1]=='a')
       s.replace(i,2,L'Ẩ');
//code chuyển chữ A mà sau nó là các dấu và A
   if(s[i]==L'Á'&&s[i+1]=='A')
       s.replace(i,2,L'Ấ');
   if(s[i]==L'À'&&s[i+1]=='A')
       s.replace(i,2,L'Ầ');
   if(s[i]==L'Ạ'&&s[i+1]=='A')
       s.replace(i,2,L'Ậ');
   if(s[i]==L'Ã'&&s[i+1]=='A')
       s.replace(i,2,L'Ẫ');
   if(s[i]==L'Ả'&&s[i+1]=='A')
       s.replace(i,2,L'Ẩ');
//code chuyển chữ e sau nó là các dấu và e
   if(s[i]==L'é'&&s[i+1]=='e')
       s.replace(i,2,L'ế');
   if(s[i]==L'è'&&s[i+1]=='e')
       s.replace(i,2,L'ề');
   if(s[i]==L'ẹ'&&s[i+1]=='e')
       s.replace(i,2,L'ệ');
   if(s[i]==L'ẽ'&&s[i+1]=='e')
       s.replace(i,2,L'ễ');
   if(s[i]==L'ẻ'&&s[i+1]=='e')
       s.replace(i,2,L'ể');
//code chuyển chữ E sau nó là các dấu và e
   if(s[i]==L'É'&&s[i+1]=='e')
       s.replace(i,2,L'Ế');
   if(s[i]==L'È'&&s[i+1]=='e')
       s.replace(i,2,L'Ề');
   if(s[i]==L'Ẹ'&&s[i+1]=='e')
       s.replace(i,2,L'Ệ');
   if(s[i]==L'Ẽ'&&s[i+1]=='e')
       s.replace(i,2,L'Ễ');
   if(s[i]==L'Ẻ'&&s[i+1]=='e')
       s.replace(i,2,L'Ể');
//code chuyển chữ E sau nó là các dấu và E
   if(s[i]==L'É'&&s[i+1]=='E')
       s.replace(i,2,L'Ế');
   if(s[i]==L'È'&&s[i+1]=='E')
       s.replace(i,2,L'Ề');
   if(s[i]==L'Ẹ'&&s[i+1]=='E')
       s.replace(i,2,L'Ệ');
   if(s[i]==L'Ẽ'&&s[i+1]=='E')
       s.replace(i,2,L'Ễ');
   if(s[i]==L'Ẻ'&&s[i+1]=='E')
       s.replace(i,2,L'Ể');
//code chuyển chữ o sau nó là các dấu và o
   if(s[i]==L'ó'&&s[i+1]=='o')
       s.replace(i,2,L'ố');
   if(s[i]==L'ò'&&s[i+1]=='o')
       s.replace(i,2,L'ồ');
   if(s[i]==L'ọ'&&s[i+1]=='o')
       s.replace(i,2,L'ộ');
   if(s[i]==L'õ'&&s[i+1]=='o')
       s.replace(i,2,L'ỗ');
   if(s[i]==L'ỏ'&&s[i+1]=='o')
       s.replace(i,2,L'ổ');
//code chuyển chữ O(hoa) sau nó là dấu và o(thường)
   if(s[i]==L'Ó'&&s[i+1]=='o')
       s.replace(i,2,L'Ố');
   if(s[i]==L'Ò'&&s[i+1]=='o')
       s.replace(i,2,L'Ồ');
   if(s[i]==L'Ọ'&&s[i+1]=='o')
       s.replace(i,2,L'Ộ');
   if(s[i]==L'Õ'&&s[i+1]=='o')
       s.replace(i,2,L'Ỗ');
   if(s[i]==L'Ỏ'&&s[i+1]=='o')
       s.replace(i,2,L'Ổ');
//code chuyển chữ O(hoa) sau nó là dấu và O(hoa)
   if(s[i]==L'Ó'&&s[i+1]=='O')
       s.replace(i,2,L'Ố');
   if(s[i]==L'Ò'&&s[i+1]=='O')
       s.replace(i,2,L'Ồ');
   if(s[i]==L'Ọ'&&s[i+1]=='O')
       s.replace(i,2,L'Ộ');
   if(s[i]==L'Õ'&&s[i+1]=='O')
       s.replace(i,2,L'Ỗ');
   if(s[i]==L'Ỏ'&&s[i+1]=='O')
       s.replace(i,2,L'Ổ');
//code chuyển chữ o sau nó là dấu và w
   if(s[i]==L'ó'&&s[i+1]=='w')
       s.replace(i,2,L'ớ');
   if(s[i]==L'ò'&&s[i+1]=='w')
       s.replace(i,2,L'ờ');
   if(s[i]==L'ọ'&&s[i+1]=='w')
       s.replace(i,2,L'ợ');
   if(s[i]==L'õ'&&s[i+1]=='w')
       s.replace(i,2,L'ỡ');
   if(s[i]==L'ỏ'&&s[i+1]=='w')
       s.replace(i,2,L'ở');
//code chuyển chữ O(hoa) sau nó là dấu và w
   if(s[i]==L'Ó'&&s[i+1]=='w')
       s.replace(i,2,L'Ớ');
   if(s[i]==L'Ò'&&s[i+1]=='w')
       s.replace(i,2,L'Ờ');
   if(s[i]==L'Ọ'&&s[i+1]=='w')
       s.replace(i,2,L'Ợ');
   if(s[i]==L'Õ'&&s[i+1]=='w')
       s.replace(i,2,L'Ỡ');
   if(s[i]==L'Ỏ'&&s[i+1]=='w')
       s.replace(i,2,L'Ở');
//code chuyển chữ O(hoa) sau nó là dấu và W(hoa)
   if(s[i]==L'Ó'&&s[i+1]=='W')
       s.replace(i,2,L'Ớ');
   if(s[i]==L'Ò'&&s[i+1]=='W')
       s.replace(i,2,L'Ờ');
   if(s[i]==L'Ọ'&&s[i+1]=='W')
       s.replace(i,2,L'Ợ');
   if(s[i]==L'Õ'&&s[i+1]=='W')
       s.replace(i,2,L'Ỡ');
   if(s[i]==L'Ỏ'&&s[i+1]=='W')
       s.replace(i,2,L'Ở');
//code chuyển chữ u sau nó là dấu và w
   if(s[i]==L'ú'&&s[i+1]=='w')
       s.replace(i,2,L'ứ');
   if(s[i]==L'ù'&&s[i+1]=='w')
       s.replace(i,2,L'ừ');
   if(s[i]==L'ụ'&&s[i+1]=='w')
       s.replace(i,2,L'ự');
   if(s[i]==L'ũ'&&s[i+1]=='w')
       s.replace(i,2,L'ữ');
   if(s[i]==L'ủ'&&s[i+1]=='w')
       s.replace(i,2,L'ử');
//code chuyển chữ U sau nó là dấu và w
   if(s[i]==L'Ú'&&s[i+1]=='w')
       s.replace(i,2,L'Ứ');
   if(s[i]==L'Ù'&&s[i+1]=='w')
       s.replace(i,2,L'Ừ');
   if(s[i]==L'Ụ'&&s[i+1]=='w')
       s.replace(i,2,L'Ự');
   if(s[i]==L'Ũ'&&s[i+1]=='w')
       s.replace(i,2,L'Ữ');
   if(s[i]==L'Ủ'&&s[i+1]=='w')
       s.replace(i,2,L'Ử');
//code chuyển chữ U sau nó là dấu và W
   if(s[i]==L'Ú'&&s[i+1]=='W')
       s.replace(i,2,L'Ứ');
   if(s[i]==L'Ù'&&s[i+1]=='W')
       s.replace(i,2,L'Ừ');
   if(s[i]==L'Ụ'&&s[i+1]=='W')
       s.replace(i,2,L'Ự');
   if(s[i]==L'Ũ'&&s[i+1]=='W')
       s.replace(i,2,L'Ữ');
   if(s[i]==L'Ủ'&&s[i+1]=='W')
       s.replace(i,2,L'Ử');
}

//viết tiếng việt theo kiểu VNI

for(int i=0;i<s.size();i++)
{
//chữ a 8 chuyển thành chữ ă
if(s[i]=='a'&&s[i+1]=='8')
  s.replace(i,2,L'ă');
if(s[i]=='A'&&s[i+1]=='8')
  s.replace(i,2,L'Ă');
//chữ a 6 chuyển thành chữ â
if(s[i]=='a'&&s[i+1]=='6')
  s.replace(i,2,L'â');
if(s[i]=='A'&&s[i+1]=='6')
  s.replace(i,2,L'Â');
//chuyển d 9 thành chữ đ
if(s[i]=='d'&&s[i+1]=='9')
  s.replace(i,2,L'đ');
if(s[i]=='D'&&s[i+1]=='9')
  s.replace(i,2,L'Đ');
//chữ e 6 chuyển thành chư ê
if(s[i]=='e'&&s[i+1]=='6')
  s.replace(i,2,L'ê');
if(s[i]=='E'&&s[i+1]=='6')
  s.replace(i,2,L'Ê');
//chữ o 7 chuyển thành chữ ơ
if(s[i]=='o'&&s[i+1]=='7')
  s.replace(i,2,L'ơ');
if(s[i]=='O'&&s[i+1]=='7')
  s.replace(i,2,L'Ơ');
//chữ o 6 chuyển thành chữ ô
if(s[i]=='o'&&s[i+1]=='6')
  s.replace(i,2,L'ô');
if(s[i]=='O'&&s[i+1]=='6')
  s.replace(i,2,L'Ô');
//chữ u 7 chuyển thành chữ ư
if(s[i]=='u'&&s[i+1]=='7')
  s.replace(i,2,L'ư');
if(s[i]=='U'&&s[i+1]=='7')
  s.replace(i,2,L'Ư');

//code chuyển chữ a
if(s[i]=='a'&&s[i+1]=='1')
  s.replace(i,2,L'á');
if(s[i]=='a'&&s[i+1]=='2')
  s.replace(i,2,L'à');
if(s[i]=='a'&&s[i+1]=='3')
  s.replace(i,2,L'ả');
if(s[i]=='a'&&s[i+1]=='4')
  s.replace(i,2,L'ã');
if(s[i]=='a'&&s[i+1]=='5')
  s.replace(i,2,L'ạ');
//code chuyển chữ A
if(s[i]=='A'&&s[i+1]=='1')
  s.replace(i,2,L'Á');
if(s[i]=='A'&&s[i+1]=='2')
  s.replace(i,2,L'À');
if(s[i]=='A'&&s[i+1]=='3')
  s.replace(i,2,L'Ả');
if(s[i]=='A'&&s[i+1]=='4')
  s.replace(i,2,L'Ã');
if(s[i]=='A'&&s[i+1]=='5')
  s.replace(i,2,L'Ả');
//code chuyển chữ ă
if(s[i]==L'ă'&&s[i+1]=='1')
  s.replace(i,2,L'ắ');
if(s[i]==L'ă'&&s[i+1]=='2')
  s.replace(i,2,L'ằ');
if(s[i]==L'ă'&&s[i+1]=='3')
  s.replace(i,2,L'ẳ');
if(s[i]==L'ă'&&s[i+1]=='4')
  s.replace(i,2,L'ẵ');
if(s[i]==L'ă'&&s[i+1]=='5')
  s.replace(i,2,L'ặ');
//code chuyển chữ Ă
if(s[i]==L'Ă'&&s[i+1]=='1')
  s.replace(i,2,L'Ắ');
if(s[i]==L'Ă'&&s[i+1]=='2')
  s.replace(i,2,L'Ằ');
if(s[i]==L'Ă'&&s[i+1]=='3')
  s.replace(i,2,L'Ẳ');
if(s[i]==L'Ă'&&s[i+1]=='4')
  s.replace(i,2,L'Ẵ');
if(s[i]==L'Ă'&&s[i+1]=='1')
  s.replace(i,2,L'Ặ');
//code chuyển chữ â
if(s[i]==L'â'&&s[i+1]=='1')
  s.replace(i,2,L'ấ');
if(s[i]==L'â'&&s[i+1]=='2')
  s.replace(i,2,L'ầ');
if(s[i]==L'â'&&s[i+1]=='3')
 s.replace(i,2,L'ẩ');
if(s[i]==L'â'&&s[i+1]=='4')
  s.replace(i,2,L'ẫ');
if(s[i]==L'â'&&s[i+1]=='5')
  s.replace(i,2,L'ậ');
//code chuyển chữ Â
if(s[i]==L'Â'&&s[i+1]=='1')
  s.replace(i,2,L'Ấ');
if(s[i]==L'Â'&&s[i+1]=='2')
  s.replace(i,2,L'Ầ');
if(s[i]==L'Â'&&s[i+1]=='3')
  s.replace(i,2,L'Ẩ');
if(s[i]==L'Â'&&s[i+1]=='4')
  s.replace(i,2,L'Ẫ');
if(s[i]==L'Â'&&s[i+1]=='5')
  s.replace(i,2,L'Ậ');
//code chuyển chữ e
if(s[i]=='e'&&s[i+1]=='1')
  s.replace(i,2,L'é');
if(s[i]=='e'&&s[i+1]=='2')
  s.replace(i,2,L'è');
if(s[i]=='e'&&s[i+1]=='3')
  s.replace(i,2,L'ẻ');
if(s[i]=='e'&&s[i+1]=='4')
  s.replace(i,2,L'ẽ');
if(s[i]=='e'&&s[i+1]=='5')
  s.replace(i,2,L'ẹ');
//code chuyển chữ E
if(s[i]=='E'&&s[i+1]=='1')
  s.replace(i,2,L'É');
if(s[i]=='E'&&s[i+1]=='2')
  s.replace(i,2,L'È');
if(s[i]=='E'&&s[i+1]=='3')
  s.replace(i,2,L'Ẻ');
if(s[i]=='E'&&s[i+1]=='4')
  s.replace(i,2,L'Ẽ');
if(s[i]=='E'&&s[i+1]=='5')
  s.replace(i,2,L'Ẹ');
//code chuyển chữ ê
if(s[i]==L'ê'&&s[i+1]=='1')
  s.replace(i,2,L'ế');
if(s[i]==L'ê'&&s[i+1]=='2')
  s.replace(i,2,L'ề');
if(s[i]==L'ê'&&s[i+1]=='3')
  s.replace(i,2,L'ể');
if(s[i]==L'ê'&&s[i+1]=='4')
  s.replace(i,2,L'ễ');
if(s[i]==L'ê'&&s[i+1]=='5')
  s.replace(i,2,L'ệ');
//code chuyển chữ Ê
if(s[i]==L'Ê'&&s[i+1]=='1')
  s.replace(i,2,L'Ế');
if(s[i]==L'Ê'&&s[i+1]=='2')
  s.replace(i,2,L'Ề');
if(s[i]==L'Ê'&&s[i+1]=='3')
  s.replace(i,2,L'Ể');
if(s[i]==L'Ê'&&s[i+1]=='4')
  s.replace(i,2,L'Ễ');
if(s[i]==L'Ê'&&s[i+1]=='5')
  s.replace(i,2,L'Ệ');
//code chuyển chữ i
if(s[i]=='i'&&s[i+1]=='1')
  s.replace(i,2,L'í');
if(s[i]=='i'&&s[i+1]=='2')
  s.replace(i,2,L'ì');
if(s[i]=='i'&&s[i+1]=='3')
  s.replace(i,2,L'ỉ');
if(s[i]=='i'&&s[i+1]=='4')
  s.replace(i,2,L'ĩ');
if(s[i]=='i'&&s[i+1]=='5')
  s.replace(i,2,L'ỉ');
//code chuyển chữ I
if(s[i]=='I'&&s[i+1]=='1')
 s.replace(i,2,L'Í');
if(s[i]=='I'&&s[i+1]=='2')
  s.replace(i,2,L'Ì');
if(s[i]=='I'&&s[i+1]=='3')
 s.replace(i,2,L'Ỉ');
if(s[i]=='I'&&s[i+1]=='4')
  s.replace(i,2,L'Ĩ');
if(s[i]=='I'&&s[i+1]=='5')
  s.replace(i,2,L'Ị');
//code chuyển chữ o
if(s[i]=='o'&&s[i+1]=='1')
 s.replace(i,2,L'ó');
if(s[i]=='o'&&s[i+1]=='2')
  s.replace(i,2,L'ò');
if(s[i]=='o'&&s[i+1]=='3')
 s.replace(i,2,L'ỏ');
if(s[i]=='o'&&s[i+1]=='4')
  s.replace(i,2,L'õ');
if(s[i]=='o'&&s[i+1]=='5')
  s.replace(i,2,L'ọ');
//code chuyển chữ O
if(s[i]=='O'&&s[i+1]=='1')
  s.replace(i,2,L'Ó');
if(s[i]=='O'&&s[i+1]=='2')
  s.replace(i,2,L'Ò');
if(s[i]=='O'&&s[i+1]=='3')
  s.replace(i,2,L'Ỏ');
if(s[i]=='O'&&s[i+1]=='4')
  s.replace(i,2,L'Õ');
if(s[i]=='O'&&s[i+1]=='5')
  s.replace(i,2,L'Ọ');
//code chuyển chữ ơ
if(s[i]==L'ơ'&&s[i+1]=='1')
  s.replace(i,2,L'ớ');
if(s[i]==L'ơ'&&s[i+1]=='2')
  s.replace(i,2,L'ờ');
if(s[i]==L'ơ'&&s[i+1]=='3')
  s.replace(i,2,L'ở');
if(s[i]==L'ơ'&&s[i+1]=='4')
  s.replace(i,2,L'ỡ');
if(s[i]==L'ơ'&&s[i+1]=='5')
  s.replace(i,2,L'ợ');
//code chuyển chữ Ô
if(s[i]==L'Ô'&&s[i+1]=='1')
  s.replace(i,2,L'Ố');
if(s[i]==L'Ô'&&s[i+1]=='2')
  s.replace(i,2,L'Ồ');
if(s[i]==L'Ô'&&s[i+1]=='3')
  s.replace(i,2,L'Ổ');
if(s[i]==L'Ô'&&s[i+1]=='4')
  s.replace(i,2,L'Ỗ');
if(s[i]==L'Ô'&&s[i+1]=='5')
  s.replace(i,2,L'Ộ');
//code chuyển  chữ u
if(s[i]=='u'&&s[i+1]=='1')
 s.replace(i,2,L'ú');
if(s[i]=='u'&&s[i+1]=='2')
  s.replace(i,2,L'ù');
if(s[i]=='u'&&s[i+1]=='3')
  s.replace(i,2,L'ủ');
if(s[i]=='u'&&s[i+1]=='4')
  s.replace(i,2,L'ũ');
if(s[i]=='u'&&s[i+1]=='5')
  s.replace(i,2,L'ụ');
//code chuyển chữ U
if(s[i]=='U'&&s[i+1]=='1')
  s.replace(i,2,L'Ú');
if(s[i]=='U'&&s[i+1]=='2')
  s.replace(i,2,L'Ù');
if(s[i]=='U'&&s[i+1]=='3')
  s.replace(i,2,L'Ủ');
if(s[i]=='U'&&s[i+1]=='4')
  s.replace(i,2,L'Ũ');
if(s[i]=='U'&&s[i+1]=='5')
  s.replace(i,2,L'Ụ');
//code chuyển chữ ư
if(s[i]==L'ư'&&s[i+1]=='1')
  s.replace(i,2,L'ứ');
if(s[i]==L'ư'&&s[i+1]=='2')
  s.replace(i,2,L'ừ');
if(s[i]==L'ư'&&s[i+1]=='3')
  s.replace(i,2,L'ử');
if(s[i]==L'ư'&&s[i+1]=='4')
  s.replace(i,2,L'ữ');;
if(s[i]==L'ư'&&s[i+1]=='5')
  s.replace(i,2,L'ự');
//code chuyển chữ Ư
if(s[i]==L'Ư'&&s[i+1]=='1')
 s.replace(i,2,L'Ứ');
if(s[i]==L'Ư'&&s[i+1]=='2')
  s.replace(i,2,L'Ừ');
if(s[i]==L'Ư'&&s[i+1]=='3')
  s.replace(i,2,L'Ử');
if(s[i]==L'Ư'&&s[i+1]=='4')
  s.replace(i,2,L'Ữ');
if(s[i]==L'Ư'&&s[i+1]=='5')
  s.replace(i,2,L'Ự');
//code chuyển chữ y
if(s[i]=='y'&&s[i+1]=='1')
  s.replace(i,2,L'ý');
if(s[i]=='y'&&s[i+1]=='2')
  s.replace(i,2,L'ỳ');
if(s[i]=='y'&&s[i+1]=='3')
  s.replace(i,2,L'ỷ');
if(s[i]=='y'&&s[i+1]=='4')
  s.replace(i,2,L'ỹ');
if(s[i]=='y'&&s[i+1]=='5')
  s.replace(i,2,L'ỵ');
//code chuyển chữ Y
if(s[i]=='Y'&&s[i+1]=='1')
  s.replace(i,2,L'Ý');
if(s[i]=='Y'&&s[i+1]=='2')
 s.replace(i,2,L'Ỳ');
if(s[i]=='Y'&&s[i+1]=='3')
  s.replace(i,2,L'Ỷ');
if(s[i]=='Y'&&s[i+1]=='4')
  s.replace(i,2,L'Ỹ');
if(s[i]=='Y'&&s[i+1]=='5')
  s.replace(i,2,L'Ỵ');
//code chuyển chữ a mà sau nó là các dấu và 8
if(s[i]==L'á'&&s[i+1]=='8')
  s.replace(i,2,L'ắ');
if(s[i]==L'à'&&s[i+1]=='8')
  s.replace(i,2,L'ằ');
if(s[i]==L'ả'&&s[i+1]=='8')
  s.replace(i,2,L'ẳ');
if(s[i]==L'ã'&&s[i+1]=='8')
  s.replace(i,2,L'ẵ');
if(s[i]==L'ạ'&&s[i+1]=='8')
  s.replace(i,2,L'ặ');
//code chuyển chữ A mà sau nó là các dấu và 8
if(s[i]==L'Á'&&s[i+1]=='8')
  s.replace(i,2,L'Ắ');
if(s[i]==L'À'&&s[i+1]=='8')
  s.replace(i,2,L'Ằ');
if(s[i]==L'Ả'&&s[i+1]=='8')
  s.replace(i,2,L'Ẳ');
if(s[i]==L'Ã'&&s[i+1]=='8')
  s.replace(i,2,L'Ẵ');
if(s[i]==L'Ạ'&&s[i+1]=='8')
  s.replace(i,2,L'Ặ');
//code chuyển chữ a mà sau nó là các dấu và 6
if(s[i]==L'á'&&s[i+1]=='6')
  s.replace(i,2,L'ấ');
if(s[i]==L'à'&&s[i+1]=='6')
  s.replace(i,2,L'ầ');
if(s[i]==L'ả'&&s[i+1]=='6')
  s.replace(i,2,L'ẩ');
if(s[i]==L'ã'&&s[i+1]=='6')
  s.replace(i,2,L'ẫ');
if(s[i]==L'ạ'&&s[i+1]=='6')
  s.replace(i,2,L'ậ');
//code chuyển chữ A mà sau nó là các dấu và 6
if(s[i]==L'Á'&&s[i+1]=='6')
  s.replace(i,2,L'Ấ');
if(s[i]==L'À'&&s[i+1]=='6')
  s.replace(i,2,L'Ầ');
if(s[i]==L'Ả'&&s[i+1]=='6')
  s.replace(i,2,L'Ẩ');
if(s[i]==L'Ã'&&s[i+1]=='6')
  s.replace(i,2,L'Ẫ');
if(s[i]==L'Ạ'&&s[i+1]=='6')
  s.replace(i,2,L'Ậ');
//code chuyển chữ e mà sau nó là các dấu và 6
if(s[i]==L'é'&&s[i+1]=='6')
  s.replace(i,2,L'ế');
if(s[i]==L'è'&&s[i+1]=='6')
  s.replace(i,2,L'ề');
if(s[i]==L'ẻ'&&s[i+1]=='6')
  s.replace(i,2,L'ể');
if(s[i]==L'ẽ'&&s[i+1]=='6')
  s.replace(i,2,L'ễ');
if(s[i]==L'ẹ'&&s[i+1]=='6')
  s.replace(i,2,L'ệ');
//code chuyển chữ E mà sau nó là các dấu và 6
if(s[i]==L'É'&&s[i+1]=='6')
  s.replace(i,2,L'Ế');
if(s[i]==L'È'&&s[i+1]=='6')
  s.replace(i,2,L'Ề');
if(s[i]==L'Ẻ'&&s[i+1]=='6')
  s.replace(i,2,L'Ể');
if(s[i]==L'Ẽ'&&s[i+1]=='6')
  s.replace(i,2,L'Ễ');
if(s[i]==L'Ẹ'&&s[i+1]=='6')
  s.replace(i,2,L'Ệ');
//code chuyển chữ o mà sau nó là các dấu và 7
if(s[i]==L'ó'&&s[i+1]=='7')
  s.replace(i,2,L'ớ');
if(s[i]==L'ò'&&s[i+1]=='7')
  s.replace(i,2,L'ờ');
if(s[i]==L'ỏ'&&s[i+1]=='7')
  s.replace(i,2,L'ở');
if(s[i]==L'õ'&&s[i+1]=='7')
  s.replace(i,2,L'ỡ');
if(s[i]==L'ọ'&&s[i+1]=='7')
  s.replace(i,2,L'ợ');
//code chuyển chữ O(hoa) mà sau nó là các dấu và 7
if(s[i]==L'Ó'&&s[i+1]=='7')
  s.replace(i,2,L'Ớ');
if(s[i]==L'Ò'&&s[i+1]=='7')
  s.replace(i,2,L'Ờ');
if(s[i]==L'Ỏ'&&s[i+1]=='7')
  s.replace(i,2,L'Ở');
if(s[i]==L'Õ'&&s[i+1]=='7')
  s.replace(i,2,L'Ỡ');
if(s[i]==L'Ọ'&&s[i+1]=='7')
  s.replace(i,2,L'Ợ');
//code chuyển chữ o mà sau nó là các dấu và 6
if(s[i]==L'ó'&&s[i+1]=='6')
  s.replace(i,2,L'ố');
if(s[i]==L'ò'&&s[i+1]=='6')
  s.replace(i,2,L'ồ');
if(s[i]==L'ỏ'&&s[i+1]=='6')
  s.replace(i,2,L'ổ');
if(s[i]==L'õ'&&s[i+1]=='6')
  s.replace(i,2,L'ỗ');
if(s[i]==L'ọ'&&s[i+1]=='6')
  s.replace(i,2,L'ộ');
//code chuyển chữ O(hoa) mà sau đó là các dấu và 6
if(s[i]==L'Ó'&&s[i+1]=='6')
  s.replace(i,2,L'Ố');
if(s[i]==L'Ò'&&s[i+1]=='6')
  s.replace(i,2,L'Ồ');
if(s[i]==L'Ỏ'&&s[i+1]=='6')
  s.replace(i,2,L'Ổ');
if(s[i]==L'Õ'&&s[i+1]=='6')
  s.replace(i,2,L'Ỗ');
if(s[i]==L'Ọ'&&s[i+1]=='6')
  s.replace(i,2,L'Ộ');
//code chuyển chữ u mà sau nó là các dấu và 7
if(s[i]==L'ú'&&s[i+1]=='7')
  s.replace(i,2,L'ứ');
if(s[i]==L'ù'&&s[i+1]=='7')
  s.replace(i,2,L'ừ');
if(s[i]==L'ủ'&&s[i+1]=='7')
  s.replace(i,2,L'ử');
if(s[i]==L'ũ'&&s[i+1]=='7')
  s.replace(i,2,L'ữ');
if(s[i]==L'ụ'&&s[i+1]=='7')
  s.replace(i,2,L'ự');
//code chuyển chữ U mà sau đó là các dấu và 7
if(s[i]==L'Ú'&&s[i+1]=='7')
  s.replace(i,2,L'Ứ');
if(s[i]==L'Ù'&&s[i+1]=='7')
  s.replace(i,2,L'Ừ');
if(s[i]==L'Ủ'&&s[i+1]=='7')
  s.replace(i,2,L'Ử');
if(s[i]==L'Ũ'&&s[i+1]=='7')
  s.replace(i,2,L'Ữ');
if(s[i]==L'Ụ'&&s[i+1]=='7')
  s.replace(i,2,L'Ự');
}
}
void MainWindow::tudongthemdaucham(QString &s)
{
    //thêm dấu chấm vào cuối đoạn nếu chưa có dấu . ! ?
        for(int i=0;i<s.size();i++)
        {
            if(s[i].isLower()&&(s[i+1]!='.'&&s[i+1]!='!'&&s[i+1]!='?')&&s[i+2]=='\n')
                s.insert(i+2,".");
            if(s[i].isUpper()&&(s[i+1]!='.'&&s[i+1]!='!'&&s[i+1]!='?')&&s[i+2]=='\n')
                s.insert(i+2,".");
            if((s[i]=='!'&&s[i]=='?'&&s[i]=='.')&&s[i+1]=='\n')
                s.insert(i+2,"\r\n");


        }
}


void MainWindow::on_actionL_u_d_i_d_ng_PDF_triggered()
{
    QString pd;
    pd=ui->textEdit->toPlainText();
    if(pd.isEmpty())
        QMessageBox::critical(this,QString::fromUtf8("Trống!"),QString::fromUtf8("Văn bản trống không thể lưu!"));
      else
    {
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->document()->print(&printer);
    }
    }
}

void MainWindow::on_actionIn_triggered()
{
    if(!ui->textEdit->toPlainText().isEmpty())
    {
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (ui->textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(QString::fromUtf8("In văn bản"));
    if (dlg->exec() == QDialog::Accepted) {
        ui->textEdit->print(&printer);
    }
    delete dlg;
#endif
    }
    else
        QMessageBox::critical(this,QString::fromUtf8("Trống!"),QString::fromUtf8("Văn bản trống không thể in!"));
}
void MainWindow::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->actionB->isChecked() ? QFont::Bold : QFont::Normal);
    thayDoiDinhDangText(fmt);
}

void MainWindow::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->actionG_ch_ch_n->isChecked());
    thayDoiDinhDangText(fmt);
}

void MainWindow::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->actionIn_nghi_ng->isChecked());
    thayDoiDinhDangText(fmt);
}
void MainWindow::thayDoiDinhDangText(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}
void MainWindow::fontChanged(const QFont &f)
{
    ui->fontComboBox->setCurrentIndex(ui->fontComboBox->findText(QFontInfo(f).family()));
    ui->comboBoxFont->setCurrentIndex(ui->comboBoxFont->findText(QString::number(f.pointSize())));
    ui->actionB->setChecked(f.bold());
    ui->actionIn_nghi_ng->setChecked(f.italic());
    ui->actionG_ch_ch_n->setChecked(f.underline());
    ui->textEdit->font();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QCloseEvent>
#include<QTextCharFormat>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void chuanhoavanban(QString &s);
    void luidaudong(QString &xau);
    void botuviettat(QString &str);
    QString xauxemtruoc() ;
    bool thaytheviettat();
    bool tuthemdaucham();
    bool sualoikieugo();
    void tudongthemdaucham(QString &s);
    void tudongsualoikieugo(QString &s);
private slots:
    void on_actionSetting_triggered();
    void on_actionVersion_triggered();
    void on_actionAbouUs_triggered();
    void on_actioWork_triggered();
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionFind_triggered();
    void on_actionChuanHoaVanBan_triggered();
    void on_actionBoTuVietTat_triggered();
    void on_actionReplace_triggered();
    void on_actionVanBanSauChinhSua_triggered();
    void on_actionAboutProject_triggered();
    void on_actionL_u_d_i_d_ng_PDF_triggered();
    void thayDoiDinhDangText(const QTextCharFormat &format);
    void textSize(const QString &p);
    void on_actionIn_triggered();
    void textUnderline();
    void textItalic();
    void textBold();


protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    void fontChanged(const QFont &f);
};

#endif // MAINWINDOW_H

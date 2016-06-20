#include "settings.h"
#include "ui_settings.h"
#include<QString>
#include<QSettings>
#include<QDebug>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    LoadSetting();
    setWindowTitle(QString::fromUtf8("Cài đặt"));


}
void Settings::LoadSetting()
{
    QSettings setting("57TH1","VietPlus");
    setting.beginGroup("SaveSettings");
    ui->checkBoxThemdaucham->setChecked(setting.value("themdaucham").toBool());

    ui->checkBoxLuidaudong->setChecked(setting.value("themdaucach").toBool());
    ui->checkBoxThaythetuviettat->setChecked(setting.value("thaythetu").toBool());
    ui->checkBoxLoikieugo->setChecked(setting.value("thaytheloikieugo").toBool());
    ui->comboBoxdaucach->setCurrentIndex(setting.value("sodaucach").toInt());

    setting.endGroup();
}
void Settings::SaveSetting()
{
    QSettings setting("57TH1","VietPlus");
    setting.beginGroup("SaveSettings");
    setting.setValue("themdaucham",ui->checkBoxThemdaucham->isChecked());

    setting.setValue("themdaucach",ui->checkBoxLuidaudong->isChecked());
    setting.setValue("thaythetu",ui->checkBoxThaythetuviettat->isChecked());
    setting.setValue("sodaucach",ui->comboBoxdaucach->currentIndex());

    setting.setValue("thaytheloikieugo",ui->checkBoxLoikieugo->isChecked());
    setting.endGroup();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButtonHuybo_clicked()
{
    this->close();
}

void Settings::on_pushButtonXacnhan_clicked()
{
    SaveSetting();
    accept();
    this->close();



}
int Settings::sodaucach()
{
    if(ui->checkBoxLuidaudong->isChecked())
        return ui->comboBoxdaucach->currentIndex();
    else
        return -1;
}
bool Settings::tudongthemdaucham()
{
    if(ui->checkBoxThemdaucham->isChecked())
        return true;
    else
        return false;
}
bool Settings::tudongsualoikieugo()
{
    if(ui->checkBoxLoikieugo->isChecked())
        return true;
    else
        return false;
}
bool Settings::tudongthaythetuviettat()
{
    if(ui->checkBoxThaythetuviettat->isChecked())
        return true;
    else
        return false;
}


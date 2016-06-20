#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include<QSettings>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    int sodaucach();
    bool tudongthemdaucham();
    bool tudongthaythetuviettat();
    bool tudongsualoikieugo();




private slots:
    void on_pushButtonHuybo_clicked();

    void on_pushButtonXacnhan_clicked();

private:
    Ui::Settings *ui;
    void SaveSetting();
    void LoadSetting();
};

#endif // SETTINGS_H

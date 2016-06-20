#ifndef THAYTHE_H
#define THAYTHE_H

#include <QDialog>

namespace Ui {
class Thaythe;
}

class Thaythe : public QDialog
{
    Q_OBJECT

public:
    explicit Thaythe(QWidget *parent = 0);
    ~Thaythe();
    QString bithaythe() const;
    QString sethaythe() const;

private slots:
    void on_pushButtonXn_clicked();

    void on_pushButtonhuy_clicked();

private:
    Ui::Thaythe *ui;
};

#endif // THAYTHE_H

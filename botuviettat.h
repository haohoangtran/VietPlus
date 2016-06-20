#ifndef BOTUVIETTAT_H
#define BOTUVIETTAT_H

#include <QDialog>

namespace Ui {
class Botuviettat;
}

class Botuviettat : public QDialog
{
    Q_OBJECT

public:
    explicit Botuviettat(QWidget *parent = 0);
    ~Botuviettat();
    QStringList tuviettat();
    QStringList tuvietchuan();

private slots:
    void on_pushButtonThem_clicked();

private:
    Ui::Botuviettat *ui;
};

#endif // BOTUVIETTAT_H

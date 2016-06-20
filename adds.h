#ifndef ADDS_H
#define ADDS_H

#include <QDialog>

namespace Ui {
class Adds;
}

class Adds : public QDialog
{
    Q_OBJECT

public:
    explicit Adds(QWidget *parent = 0);
    ~Adds();
    QString viettat() const;
    QString vietchuan() const;

private slots:
    void on_pushButtonThem_clicked();

    void on_pushButtonHuy_clicked();

private:
    Ui::Adds *ui;
};

#endif // ADDS_H

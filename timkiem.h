#ifndef TIMKIEM_H
#define TIMKIEM_H

#include <QDialog>

namespace Ui {
class Timkiem;
}

class Timkiem : public QDialog
{
    Q_OBJECT

public:
    explicit Timkiem(QWidget *parent = 0);
    ~Timkiem();
    QString timkiem() const;

private slots:
    void on_pushButtonTimkiem_clicked();

private:
    Ui::Timkiem *ui;
};

#endif // TIMKIEM_H

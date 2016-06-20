#ifndef DUAN_H
#define DUAN_H

#include <QDialog>

namespace Ui {
class Duan;
}

class Duan : public QDialog
{
    Q_OBJECT

public:
    explicit Duan(QWidget *parent = 0);
    ~Duan();

private:
    Ui::Duan *ui;
};

#endif // DUAN_H

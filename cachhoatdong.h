#ifndef CACHHOATDONG_H
#define CACHHOATDONG_H

#include <QDialog>

namespace Ui {
class Cachhoatdong;
}

class Cachhoatdong : public QDialog
{
    Q_OBJECT

public:
    explicit Cachhoatdong(QWidget *parent = 0);
    ~Cachhoatdong();

private:
    Ui::Cachhoatdong *ui;
};

#endif // CACHHOATDONG_H

#ifndef REVIEW_H
#define REVIEW_H

#include <QDialog>

namespace Ui {
class ReView;
}

class ReView : public QDialog
{
    Q_OBJECT

public:
    explicit ReView(QWidget *parent = 0);
    ~ReView();
    void datxauvao(QString &s);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ReView *ui;
};

#endif // REVIEW_H

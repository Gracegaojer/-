#ifndef ADDPAY_H
#define ADDPAY_H

#include <QDialog>

namespace Ui {
class addpay;
}

class addpay : public QDialog
{
    Q_OBJECT

public:
    explicit addpay(QWidget *parent = 0);
    ~addpay();
private slots:
    void on_addpay_signal1();
    void quit();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addpay *ui;
signals:
    void resetmain_pay();
};

#endif // ADDPAY_H

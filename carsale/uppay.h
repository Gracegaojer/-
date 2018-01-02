#ifndef UPPAY_H
#define UPPAY_H

#include <QDialog>

namespace Ui {
class uppay;
}

class uppay : public QDialog
{
    Q_OBJECT

public:
    explicit uppay(QWidget *parent = 0);
    ~uppay();
private slots:
    void on_uppay_signal1();
    void quit();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::uppay *ui;
signals:
    void resetmain_pay();
};

#endif // UPPAY_H

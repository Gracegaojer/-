#ifndef ADDSALE_H
#define ADDSALE_H

#include <QDialog>

namespace Ui {
class addsale;
}

class addsale : public QDialog
{
    Q_OBJECT

public:
    explicit addsale(QWidget *parent = 0);
    ~addsale();
public slots:
    void on_addsale_signal1();

private slots:
    void on_pushButton_clicked();
    void quit();

    void on_pushButton_2_clicked();

private:
    Ui::addsale *ui;
signals:
    void resetmain_sale();
};

#endif // ADDSALE_H

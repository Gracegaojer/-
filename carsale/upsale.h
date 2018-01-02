#ifndef UPSALE_H
#define UPSALE_H

#include <QDialog>

namespace Ui {
class upsale;
}

class upsale : public QDialog
{
    Q_OBJECT

public:
    explicit upsale(QWidget *parent = 0);
    ~upsale();
private slots:
    void quit();
    void on_upsale_signal1();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::upsale *ui;
signals:
    void resetmain_sale();
};

#endif // UPSALE_H

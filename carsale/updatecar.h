#ifndef UPDATECAR_H
#define UPDATECAR_H

#include <QDialog>

namespace Ui {
class updatecar;
}

class updatecar : public QDialog
{
    Q_OBJECT

public:
    explicit updatecar(QWidget *parent = 0);
    ~updatecar();

private slots:
    void on_pushButton_clicked();
    void on_upcar_signal1();
    void on_pushButton_2_clicked();
    void quit();

private:
    Ui::updatecar *ui;
signals:
    void resetmain_car();

};

#endif // UPDATECAR_H

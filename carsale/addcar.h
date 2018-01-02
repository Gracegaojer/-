#ifndef ADDCAR_H
#define ADDCAR_H

#include <QDialog>

namespace Ui {
class addcar;
}

class addcar : public QDialog
{
    Q_OBJECT

public:
    explicit addcar(QWidget *parent = 0);
    ~addcar();

private slots:
    void on_addcar_signal1();
    void quit();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::addcar *ui;
signals:
    void resetmain_car();

};

#endif // ADDCAR_H

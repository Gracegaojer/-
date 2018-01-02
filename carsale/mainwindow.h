#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void reset_car();
    void reset_sale();
    void reset_pay();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_Car_Sale_triggered();
    void on_car_choose1_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_car_choose2_currentIndexChanged(int index);

    void on_sale_choose_currentIndexChanged(int index);

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_action_5_triggered();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
signals:
    void showaddcar();
    void showupcar();
    void showaddsale();
    void showupsale();
    void showaddpay();
    void showuppay();
    void quit();

};

#endif // MAINWINDOW_H

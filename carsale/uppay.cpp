#include "uppay.h"
#include "ui_uppay.h"
#include "carsale.h"
extern payinfo * payinfoall;
extern QString up_car;
uppay::uppay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uppay)
{
    ui->setupUi(this);
}

uppay::~uppay()
{
    delete ui;
}
void uppay::on_uppay_signal1(){
    ui->carid->setText(payinfoall->carid);
    ui->paydate->setText(payinfoall->paydate);
    ui->pay_thistime->setText(QString("%1").arg(payinfoall->paid_thistime));
    ui->left_bill->setText(QString("%1").arg(payinfoall->left_bill));
    ui->opname->setText(payinfoall->opname);
    this->show();
}

void uppay::quit(){
    this->close();
}

void uppay::on_pushButton_clicked()
{
    payinfoall->paid_thistime=ui->pay_thistime->text().toFloat();
    payinfoall->left_bill=ui->left_bill->text().toFloat();
    strcpy(payinfoall->opname,ui->opname->text().toLatin1().data());
    pay_update(up_car.toLatin1().data(),payinfoall->carid,payinfoall->paydate,payinfoall->paid_thistime,payinfoall->left_bill,payinfoall->opname);
    this->hide();
    emit(resetmain_pay());
}

void uppay::on_pushButton_2_clicked()
{
    this->hide();
}

#include "addpay.h"
#include "ui_addpay.h"
#include "carsale.h"
extern QString up_car;
extern QString up_sale;
addpay::addpay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addpay)
{
    ui->setupUi(this);
}

addpay::~addpay()
{
    delete ui;
}
void addpay::on_addpay_signal1(){
    ui->carid->setText(up_sale);
    this->show();
}

void addpay::quit(){
    this->close();
}

void addpay::on_pushButton_clicked()//添加车辆信息
{
    char paydate[12];
    strcpy(paydate,ui->pay_date->text().toLatin1().data());
    float paid_thistime=ui->pay_thistime->text().toFloat();//交款金额
    float left_bill=ui->left_bill->text().toFloat();//未支付
    char opname[20];//收款人
    strcpy(opname,ui->opname->text().toLatin1().data());
    char carid[20];
    strcpy(carid,up_sale.toLatin1().data());
    char carname[20];
    strcpy(carname,up_car.toLatin1().data());

    payinfo * p=pay_create(carid,paydate,paid_thistime,left_bill,opname);
    pay_insert(p,carname,carid);

    this->hide();
    emit(resetmain_pay());
}

void addpay::on_pushButton_2_clicked()
{
    ui->carid->clear();
    ui->left_bill->clear();
    ui->opname->clear();
    ui->pay_date->clear();
    ui->pay_thistime->clear();
    this->hide();
}

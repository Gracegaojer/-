#include "addsale.h"
#include "ui_addsale.h"
#include"carsale.h"
extern QString up_car;

addsale::addsale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsale)
{
    ui->setupUi(this);
}

addsale::~addsale()
{
    delete ui;
}

void addsale::on_addsale_signal1(){
    ui->carname->setText(up_car);
    this->show();
}

void addsale::on_pushButton_clicked()
{
    char carid[20];
    char carname[20];
    char carcolor[10];
    char saledate[12];
    char clientname[20];
    char clientid[20];
    char clientphone[15];
    float saleprice=ui->saleprice->text().toFloat();
    strcpy(carid,ui->carid->text().toLatin1().data());
    strcpy(carname,ui->carname->text().toLatin1().data());
    strcpy(carcolor,ui->color->text().toLatin1().data());
    strcpy(saledate,ui->saledate->text().toLatin1().data());
    strcpy(clientname,ui->clientname->text().toLatin1().data());
    strcpy(clientid,ui->clientid->text().toLatin1().data());
    strcpy(clientphone,ui->clientphone->text().toLatin1().data());

    sale_insert(sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice),carname);
    ui->carid->clear();
    ui->carname->clear();
    ui->color->clear();
    ui->saledate->clear();
    ui->clientid->clear();
    ui->clientname->clear();
    ui->saleprice->clear();
    ui->clientphone->clear();

    emit(resetmain_sale());
    this->hide();
}
void addsale::quit(){
    this->close();
}

void addsale::on_pushButton_2_clicked()
{
    ui->carid->clear();
    ui->carname->clear();
    ui->color->clear();
    ui->saledate->clear();
    ui->clientid->clear();
    ui->clientname->clear();
    ui->saleprice->clear();
    ui->clientphone->clear();
    this->hide();
}

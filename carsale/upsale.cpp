#include "upsale.h"
#include "ui_upsale.h"
#include"carsale.h"

extern carinfo * car_head;
extern QString up_car;
extern QString up_sale;

upsale::upsale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::upsale)
{
    ui->setupUi(this);
}

upsale::~upsale()
{
    delete ui;
}

void upsale::quit(){
    this->close();
}
void upsale::on_upsale_signal1(){//显示

    carinfo * p=car_head->next;
    saleinfo * s;

    while(p!=0){
        if(!strcmp(up_car.toLatin1().data(),p->name)){
            s=p->sale_head->next;
            while(s!=0){
                if(!strcmp(up_sale.toLatin1().data(),s->carid)){
                    ui->carid->setText(QString("%1").arg(s->carid));
                    ui->carname->setText(QString("%1").arg(s->carname));
                    ui->carcolor->setText(QString("%1").arg(s->carcolor));
                    ui->saledate->setText(QString("%1").arg(s->saledate));
                    ui->clientname->setText(QString("%1").arg(s->clientname));
                    ui->clientid->setText(QString("%1").arg(s->clientid));
                    ui->clientphone->setText(QString("%1").arg(s->clientphone));
                    ui->saleprice->setText(QString("%1").arg(s->saleprice));
                    break;
                }
                else{s=s->next;}
            }
            break;
        }
        else{p=p->next;}
    }
    this->show();
}

void upsale::on_pushButton_clicked()
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
    strcpy(carcolor,ui->carcolor->text().toLatin1().data());
    strcpy(saledate,ui->saledate->text().toLatin1().data());
    strcpy(clientname,ui->clientname->text().toLatin1().data());
    strcpy(clientid,ui->clientid->text().toLatin1().data());
    strcpy(clientphone,ui->clientphone->text().toLatin1().data());

    sale_update(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice);
    emit(resetmain_sale());
    this->hide();
}

void upsale::on_pushButton_2_clicked()
{
    this->hide();
}

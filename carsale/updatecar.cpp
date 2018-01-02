#include "updatecar.h"
#include "ui_updatecar.h"
#include"carsale.h"
#include"qdebug.h"

extern QString up_car;
extern carinfo * car_head;
extern carinfo * car_trail;

updatecar::updatecar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updatecar)
{
    ui->setupUi(this);
}

updatecar::~updatecar()
{
    delete ui;
}

void updatecar::on_pushButton_clicked()
{
    car_update(ui->name->text().toLatin1().data(),ui->weight->text().toInt(),ui->seatnum->text().toInt(),ui->length->text().toInt(),ui->wide->text().toInt(),ui->height->text().toInt());
    emit(resetmain_car());
    this->hide();
}

void updatecar::on_upcar_signal1(){
    carinfo * p=car_head->next;
    //qDebug()<<"link"<<p->name;
    //qDebug()<<"extern"<<up_car;
    while(p!=0){
        if(!strcmp(up_car.toLatin1().data(),p->name)){
            ui->name->setText(QString(p->name));
            ui->height->setText(QString("%1").arg(p->height));
            ui->length->setText(QString("%1").arg(p->length));
            ui->seatnum->setText(QString("%1").arg(p->seatnum));
            ui->weight->setText(QString("%1").arg(p->weight));
            ui->wide->setText(QString("%1").arg(p->wide));
            break;
        }
        else{p=p->next;}
    }
    this->show();
}

void updatecar::on_pushButton_2_clicked()
{
    ui->name->clear();
    ui->weight->clear();
    ui->seatnum->clear();
    ui->length->clear();
    ui->wide->clear();
    ui->height->clear();
    this->hide();
}

void updatecar::quit(){
    this->close();
}

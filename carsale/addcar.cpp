#include "addcar.h"
#include "ui_addcar.h"
#include "carsale.h"

addcar::addcar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addcar)
{
    ui->setupUi(this);
}

addcar::~addcar()
{
    delete ui;
}

void addcar::on_pushButton_clicked()
{
    car_insert(car_create(ui->name->text().toLatin1().data(),ui->weight->text().toInt(),ui->seatnum->text().toInt(),ui->length->text().toInt(),ui->wide->text().toInt(),ui->height->text().toInt()));
    ui->name->clear();
    ui->weight->clear();
    ui->seatnum->clear();
    ui->length->clear();
    ui->wide->clear();
    ui->height->clear();
    emit(resetmain_car());
    this->hide();
}

void addcar::on_addcar_signal1()
{
    this->show();
}

void addcar::on_pushButton_2_clicked()
{
    ui->name->clear();
    ui->weight->clear();
    ui->seatnum->clear();
    ui->length->clear();
    ui->wide->clear();
    ui->height->clear();
    this->hide();
}

void addcar::quit(){
    this->close();
}

#include "mainwindow.h"
#include"addcar.h"
#include "ui_mainwindow.h"
#include"carsale.h"
#include"addsale.h"
#include"qdebug.h"
#include<qstandarditemmodel.h>
#include<malloc.h>
#include<qmessagebox.h>
#include<string.h>

extern carinfo * car_head;
extern carinfo * car_trail;
QString up_car;
QString up_sale;
payinfo* payinfoall=(payinfo*)malloc(sizeof(payinfo));

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//addcar
{
    emit(showaddcar());
}
void MainWindow::reset_car(){
    qDebug()<<"reset";
    QStandardItemModel  *carmodel = new QStandardItemModel();
    carmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车型")));
    carmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("重量（kg）")));
    carmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("座位数")));
    carmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("车长（mm）")));
    carmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("车宽（mm）")));
    carmodel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("车高（mm）")));

    int i;
    char buf[10];

    carinfo* p=car_head->next;
    for(i=0;p!=NULL;i++){
        carmodel->setItem(i,0,new QStandardItem(p->name));
        carmodel->setItem(i,1,new QStandardItem(itoa(p->weight,buf,10)));
        carmodel->setItem(i,2,new QStandardItem(itoa(p->seatnum,buf,10)));
        carmodel->setItem(i,3,new QStandardItem(itoa(p->length,buf,10)));
        carmodel->setItem(i,4,new QStandardItem(itoa(p->wide,buf,10)));
        carmodel->setItem(i,5,new QStandardItem(itoa(p->height,buf,10)));
        qDebug()<<p->name;
        p=p->next;
    }

    ui->car->setModel(carmodel);
}

void MainWindow::on_pushButton_2_clicked()//修改信息
{
    int row=ui->car->currentIndex().row();
    up_car=ui->car->model()->data(ui->car->model()->index(row,0)).toString();
   // qDebug()<<up_car;
    emit(showupcar());
}

void MainWindow::on_pushButton_3_clicked()
{
    int row=ui->car->currentIndex().row();
    QString carname=ui->car->model()->data(ui->car->model()->index(row,0)).toString();
    car_delete(carname.toLatin1().data());
    reset_car();
}

void MainWindow::on_action_triggered()
{
    emit(quit());
    this->close();
}

void MainWindow::on_action_2_triggered()
{
    QStandardItemModel  *carmodel = new QStandardItemModel();
    carmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车型")));
    carmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("重量（kg）")));
    carmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("座位数")));
    carmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("车长（mm）")));
    carmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("车宽（mm）")));
    carmodel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("车高（mm）")));
    int i;
    char buf[10];
    if(car_head->next==NULL){
        ui->car->setModel(carmodel);
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }
    carinfo* p=car_head->next;
    for(i=0;p!=NULL;i++){
        carmodel->setItem(i,0,new QStandardItem(p->name));
        carmodel->setItem(i,1,new QStandardItem(itoa(p->weight,buf,10)));
        carmodel->setItem(i,2,new QStandardItem(itoa(p->seatnum,buf,10)));
        carmodel->setItem(i,3,new QStandardItem(itoa(p->length,buf,10)));
        carmodel->setItem(i,4,new QStandardItem(itoa(p->wide,buf,10)));
        carmodel->setItem(i,5,new QStandardItem(itoa(p->height,buf,10)));
        p=p->next;
    }
    ui->car->setModel(carmodel);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_action_3_triggered()
{
    if(car_head->next==NULL){
        ui->stackedWidget->setCurrentIndex(2);
        return;
    }
    carinfo* p=car_head->next;
    ui->car_choose1->clear();
    QStringList carname;
    while(p!=0){
        carname<<QString(QLatin1String(p->name));
        p=p->next;
    }
    ui->car_choose1->addItems(carname);

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_action_4_triggered()//转到车辆缴费信息页面
{
    ui->stackedWidget->setCurrentIndex(3);
    if(car_head->next==NULL){
        ui->stackedWidget->setCurrentIndex(2);
        return;
    }
    carinfo* p=car_head->next;
    ui->car_choose2->clear();
    QStringList carname;
    while(p!=0){
        carname<<QString(QLatin1String(p->name));
        p=p->next;
    }
    ui->car_choose2->addItems(carname);

 //   on_car_choose2_currentIndexChanged(0);
 //   on_sale_choose_currentIndexChanged(0);
}

void MainWindow::on_action_5_triggered()//统计功能页面
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_action_Car_Sale_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_car_choose1_currentIndexChanged(int index)
{
    int i;
    char carnamenow[20];
    char buf[10];
    qDebug()<<ui->car_choose1->currentText();
    strcpy(carnamenow,ui->car_choose1->currentText().toLatin1().data());

    QStandardItemModel  *salemodel = new QStandardItemModel();
    salemodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车辆编号")));
    salemodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("车型")));
    salemodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("颜色")));
    salemodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("销售日期")));
    salemodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("客户姓名")));
    salemodel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("客户身份证号")));
    salemodel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("客户联系电话")));
    salemodel->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("销售价格")));

    carinfo* p=car_head;
    saleinfo* s;
    if(car_head->next==0) {
        ui->sale->setModel(salemodel);
        return;
    }
    while(p->next!=0){
        if(!strcmp(p->next->name,carnamenow)){
            if(p->next->sale_head->next!=0)
            {
                s=p->next->sale_head;
                for(i=0;s->next!=NULL;i++){
                    salemodel->setItem(i,0,new QStandardItem(s->next->carid));
                    salemodel->setItem(i,1,new QStandardItem(s->next->carname));
                    salemodel->setItem(i,2,new QStandardItem(s->next->carcolor));
                    salemodel->setItem(i,3,new QStandardItem(s->next->saledate));
                    salemodel->setItem(i,4,new QStandardItem(s->next->clientname));
                    salemodel->setItem(i,5,new QStandardItem(s->next->clientid));
                    salemodel->setItem(i,6,new QStandardItem(s->next->clientphone));
                    salemodel->setItem(i,7,new QStandardItem(sprintf(buf,"%f",s->next->saleprice)));
                    s=s->next;
                }
            }
            break;
        }
        else{
            p=p->next;
        }
    }
    ui->sale->setModel(salemodel);
}

void MainWindow::on_pushButton_5_clicked()
{
    up_car=ui->car_choose1->currentText();
    emit(showaddsale());
}

void MainWindow::reset_sale(){
    on_car_choose1_currentIndexChanged(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->sale->currentIndex().row()==-1){
        QMessageBox::warning(0, qApp->tr("warning"),tr("请选中一行进行修改！"), QMessageBox::Ok);
        return;
    }
    int row=ui->sale->currentIndex().row();
    //qDebug()<<ui->sale->model()->data(ui->sale->model()->index(row,0)).toString();
    up_car=ui->sale->model()->data(ui->sale->model()->index(row,1)).toString();
    up_sale=ui->sale->model()->data(ui->sale->model()->index(row,0)).toString();
    emit(showupsale());
}

void MainWindow::on_pushButton_6_clicked()
{
    if(ui->sale->currentIndex().row()==-1){
        QMessageBox::warning(0, qApp->tr("warning"),tr("请选中一行进行修改！"), QMessageBox::Ok);
        return;
    }
    int row=ui->sale->currentIndex().row();
    //qDebug()<<ui->sale->model()->data(ui->sale->model()->index(row,0)).toString();
    up_car=ui->sale->model()->data(ui->sale->model()->index(row,1)).toString();
    up_sale=ui->sale->model()->data(ui->sale->model()->index(row,0)).toString();
    sale_delete(up_sale.toLatin1().data(),up_car.toLatin1().data());
    reset_sale();
}

void MainWindow::on_car_choose2_currentIndexChanged(int index)//车型选择变化
{
    char carname[20];
    strcpy(carname,ui->car_choose2->currentText().toLatin1().data());
    qDebug()<<carname;
    carinfo* p=car_head;
    saleinfo* s;
    QStringList caridlist;
    while(p->next!=NULL){
        if(strcmp(p->next->name,carname)==0){
            s=p->next->sale_head;
            while(s->next!=NULL){
                caridlist<<QString(QLatin1String(s->next->carid));
                s=s->next;
            }
            break;
        }
        p=p->next;
    }
    ui->sale_choose->clear();
    ui->sale_choose->addItems(caridlist);
}

void MainWindow::on_sale_choose_currentIndexChanged(int index)//carid changed
{
    char carname[20];
    strcpy(carname,ui->car_choose2->currentText().toLatin1().data());
    char carid[20];
    strcpy(carid,ui->sale_choose->currentText().toLatin1().data());
    qDebug()<<carname<<"|"<<carid;
    carinfo* c=car_head;
    saleinfo * s;
    payinfo * p;
    int i;

    QStandardItemModel  *paymodel = new QStandardItemModel();
    paymodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车辆编号")));
    paymodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("缴费日期")));
    paymodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("缴费金额")));
    paymodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("未收余款")));
    paymodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("收款人")));

    while(c->next!=NULL){
        if(strcmp(c->next->name,carname)==0){
            s=c->next->sale_head;
            while(s->next!=NULL){
                if(strcmp(s->next->carid,carid)==0){
                    p=s->next->pay_head;
                    i=0;
                    if(p==NULL){ui->pay->setModel(paymodel);return;}
                    while(p->next!=NULL){
                        paymodel->setItem(i,0,new QStandardItem(p->next->carid));
                        paymodel->setItem(i,1,new QStandardItem(p->next->paydate));
                        paymodel->setItem(i,2,new QStandardItem(QString("%1").arg(p->next->paid_thistime)));
                        paymodel->setItem(i,3,new QStandardItem(QString("%1").arg(p->next->left_bill)));
                        paymodel->setItem(i,4,new QStandardItem(p->next->opname));
                        p=p->next;
                        i++;
                    }
                    break;
                }
                s=s->next;
            }
            break;
        }
        c=c->next;
    }

    ui->pay->setModel(paymodel);
}

void MainWindow::on_pushButton_7_clicked()
{
    up_car=ui->car_choose2->currentText();
    up_sale=ui->sale_choose->currentText();
    emit(showaddpay());
}

void MainWindow::on_pushButton_9_clicked()
{
    if(ui->pay->currentIndex().row()==-1){
        QMessageBox::warning(0, qApp->tr("warning"),tr("请选中一行进行修改！"), QMessageBox::Ok);
        return;
    }
    int row = ui->pay->currentIndex().row();
    up_car=ui->car_choose2->currentText();
    strcpy(payinfoall->carid,ui->pay->model()->data(ui->pay->model()->index(row,0)).toString().toLatin1().data());
    strcpy(payinfoall->paydate,ui->pay->model()->data(ui->pay->model()->index(row,1)).toString().toLatin1().data());
    payinfoall->paid_thistime=ui->pay->model()->data(ui->pay->model()->index(row,2)).toString().toFloat();
    payinfoall->left_bill=ui->pay->model()->data(ui->pay->model()->index(row,3)).toString().toFloat();
    strcpy(payinfoall->opname,ui->pay->model()->data(ui->pay->model()->index(row,4)).toString().toLatin1().data());
    emit(showuppay());
}

void MainWindow::reset_pay(){
    on_sale_choose_currentIndexChanged(ui->sale_choose->currentIndex());
}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->pay->currentIndex().row()==-1){
        QMessageBox::warning(0, qApp->tr("warning"),tr("请选中一行进行删除！"), QMessageBox::Ok);
        return;
    }
    int row = ui->pay->currentIndex().row();
    pay_delete(ui->car_choose2->currentText().toLatin1().data(),ui->sale_choose->currentText().toLatin1().data(),ui->pay->model()->data(ui->pay->model()->index(row,1)).toString().toLatin1().data());
    reset_pay();
}



//快速排序：由于不能根据下标进行查找，所以没有办法从右侧实现指针的逆序，所以此处两个指针同时向右运行，而新建的链表，大于基准的头插，小于基准的尾插
carinfo* QUIKSORT_sale(carinfo* head,carinfo* trail){
    carinfo* tmp;
    carinfo* left=head;
    carinfo* middle=head;
    while(left->next!=NULL&&left!=trail){
        if(left->next->salenum>middle->salenum){
            tmp=left->next;
            if(left->next->next!=NULL)
                left->next=left->next->next;
            else left->next=NULL;
            tmp->next=head;//头插法
            head=tmp;
            continue;
        }
        left=left->next;
    }
    if(head->next!=middle&&head!=middle){
        carinfo* head1=QUIKSORT_sale(head,middle);
        head=head1;
    }
    if(middle->next!=NULL&&middle->next!=trail){
        carinfo* head2=middle->next;
        middle->next=QUIKSORT_sale(head2,trail);
    }
    return head;
}

void MainWindow::on_pushButton_10_clicked()//销量统计排序
{
    if(car_head->next!=NULL){
        carinfo* head=car_head->next;
        car_head->next=QUIKSORT_sale(head,car_trail);
    }
    QStandardItemModel  *carmodel = new QStandardItemModel();
    carmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车型")));
    carmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("重量（kg）")));
    carmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("座位数")));
    carmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("车长（mm）")));
    carmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("车宽（mm）")));
    carmodel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("车高（mm）")));
    carmodel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("销量（台）")));
    int i;
    char buf[10];
    carinfo* p=car_head->next;
    for(i=0;p!=NULL;i++){
        carmodel->setItem(i,0,new QStandardItem(p->name));
        carmodel->setItem(i,1,new QStandardItem(itoa(p->weight,buf,10)));
        carmodel->setItem(i,2,new QStandardItem(itoa(p->seatnum,buf,10)));
        carmodel->setItem(i,3,new QStandardItem(itoa(p->length,buf,10)));
        carmodel->setItem(i,4,new QStandardItem(itoa(p->wide,buf,10)));
        carmodel->setItem(i,5,new QStandardItem(itoa(p->height,buf,10)));
        carmodel->setItem(i,6,new QStandardItem(itoa(p->salenum,buf,10)));
        p=p->next;
    }
    ui->tableView->setModel(carmodel);
}
carinfo* QUIKSORT_money(carinfo* head,carinfo* trail){
    carinfo* tmp;
    carinfo* left=head;
    carinfo* middle=head;
    while(left->next!=NULL&&left!=trail){
        if(left->next->salemoney>middle->salemoney){
            tmp=left->next;
            if(left->next->next!=NULL)
                left->next=left->next->next;
            else left->next=NULL;
            tmp->next=head;//头插法
            head=tmp;
            continue;
        }
        left=left->next;
    }
    if(head->next!=middle&&head!=middle){
        carinfo* head1=QUIKSORT_money(head,middle);
        head=head1;
    }
    if(middle->next!=NULL&&middle->next!=trail){
        carinfo* head2=middle->next;
        middle->next=QUIKSORT_money(head2,trail);
    }
    return head;
}
void MainWindow::on_pushButton_11_clicked()//销售额统计排序
{
    if(car_head->next!=NULL){
        carinfo* head=car_head->next;
        car_head->next=QUIKSORT_money(head,car_trail);
    }
    QStandardItemModel  *carmodel = new QStandardItemModel();
    carmodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车型")));
    carmodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("重量（kg）")));
    carmodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("座位数")));
    carmodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("车长（mm）")));
    carmodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("车宽（mm）")));
    carmodel->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("车高（mm）")));
    carmodel->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("销售额（元）")));
    int i;
    char buf[10];
    carinfo* p=car_head->next;
    for(i=0;p!=NULL;i++){
        carmodel->setItem(i,0,new QStandardItem(p->name));
        carmodel->setItem(i,1,new QStandardItem(itoa(p->weight,buf,10)));
        carmodel->setItem(i,2,new QStandardItem(itoa(p->seatnum,buf,10)));
        carmodel->setItem(i,3,new QStandardItem(itoa(p->length,buf,10)));
        carmodel->setItem(i,4,new QStandardItem(itoa(p->wide,buf,10)));
        carmodel->setItem(i,5,new QStandardItem(itoa(p->height,buf,10)));
        carmodel->setItem(i,6,new QStandardItem(itoa(p->salemoney,buf,10)));
        p=p->next;
    }
    ui->tableView->setModel(carmodel);
}

void MainWindow::on_pushButton_12_clicked()
{
    QStandardItemModel  *salemodel = new QStandardItemModel();
    salemodel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("车辆编号")));
    salemodel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("车型")));
    salemodel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("客户姓名")));
    salemodel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("客户身份证号")));
    salemodel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("客户联系电话")));

    carinfo* c=car_head;
    saleinfo* s;
    int i=0;
    while(c->next!=NULL){
        s=c->next->sale_head;
        while(s->next!=NULL){
            if(s->next->paidall==0){//需要被列出的客户
                salemodel->setItem(i,0,new QStandardItem(s->next->carid));
                salemodel->setItem(i,1,new QStandardItem(s->next->carname));
                salemodel->setItem(i,2,new QStandardItem(s->next->clientname));
                salemodel->setItem(i,3,new QStandardItem(s->next->clientid));
                salemodel->setItem(i,4,new QStandardItem(s->next->clientphone));
                i++;
            }
            s=s->next;
        }
        c=c->next;
    }
    ui->tableView->setModel(salemodel);
}

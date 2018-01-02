#include"carsale.h"
#include"addcar.h"
#include"qdebug.h"
#include "mainwindow.h"
#include <QApplication>
#include"updatecar.h"
#include"addsale.h"
#include"upsale.h"
#include"qdebug.h"
#include"addpay.h"
#include"uppay.h"
#include<QFile>


carinfo * car_head=(carinfo *)malloc(sizeof(carinfo));

carinfo * car_trail=car_head;

int main(int argc, char *argv[])
{
    //录入基础数据--car
 /*   char car[20]="fukang_1.4_hand";
    car_insert(car_create(car,500,5,4071,1402,1425));
    strcpy(car,"heihei");
    car_insert(car_create(car,100,2,2000,800,800));
    strcpy(car,"lala");
    car_insert(car_create(car,600,6,6000,2000,2000));

    //录入基础数据--sale
    char carid[20]="012006015678";
    char carname[20]="fukang_1.4_hand";
    char carcolor[10]="red";
    char saledate[12]="2007/09/03";
    char clientname[20]="zhang_ming";
    char clientid[20]="420111198001012216";
    char clientphone[15]="012345678901";
    float saleprice=75000.00;
    sale_insert(sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice),carname);
    strcpy(carid,"112006015678");
    sale_insert(sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice),carname);
    strcpy(carid,"212006015678");
    saleinfo* tmpsale=sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice);
    qDebug()<<tmpsale->carid;
    sale_insert(tmpsale,carname);

    strcpy(carid,"312006015678");
    strcpy(carname,"heihei");
    sale_insert(sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice),carname);
    strcpy(carname,"lala");
    strcpy(carid,"412006015678");
    sale_insert(sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice),carname);
    strcpy(carid,"512006015678");
    sale_insert(sale_create(carid,carname,carcolor,saledate,clientname,clientid,clientphone,saleprice),carname);

    char paydate[12]="2008/01/01";
    float paid_thistime=1000.00;//交款金额
    float left_bill=74000.00;//未支付
    char opname[20]="li_hua";//收款人
    payinfo * p=pay_create(carid,paydate,paid_thistime,left_bill,opname);
    pay_insert(p,carname,carid);

*/
    car_head->sale_head=(saleinfo*)malloc(sizeof(saleinfo));
    car_head->sale_head->next=NULL;
    car_head->sale_head->pay_head=(payinfo*)malloc(sizeof(payinfo));
    car_head->sale_head->pay_head->next=NULL;

    FILE* fp1,*fp2,*fp3;
    fp1=fopen("./data_car","rb+");
    if(!fp1){//找不到文件
        fp1=fopen("./data_car","wb+");
    }
    fp2=fopen("./data_sale","rb+");
    if(!fp2){//找不到文件
        fp2=fopen("./data_sale","wb+");
    }
    fp3=fopen("./data_pay","rb+");
    if(!fp3){//找不到文件
        fp3=fopen("./data_pay","wb+");
    }

    carinfo * car_file=(carinfo *)malloc(sizeof(carinfo));
    saleinfo * sale_file=(saleinfo*)malloc(sizeof(saleinfo));
    payinfo * pay_file=(payinfo*)malloc(sizeof(payinfo));
    int size1=sizeof(carinfo)-3*sizeof(void*);//除去指针外的相应结构体的大小
    int size2=sizeof(saleinfo)-3*sizeof(void*);
    int size3=sizeof(payinfo)-sizeof(void*);

    //读文件
    while(fread(car_file,size1,1,fp1)!=0){
        qDebug()<<car_file->name;
        car_insert(car_file);
        car_file=(carinfo *)malloc(sizeof(carinfo));
    }
    while(fread(sale_file,size2,1,fp2)!=0){
        qDebug()<<"fp2"<<sale_file->carname<<sale_file->clientname<<sale_file->clientid<<sale_file->clientphone;
        sale_insert(sale_file,sale_file->carname);
        sale_file=(saleinfo*)malloc(sizeof(saleinfo));
    }
    char _carname[20];
    while(fread(pay_file,size3,1,fp3)!=0){
        if(fread(_carname,sizeof(char),20,fp3)!=0){
        qDebug()<<"fp3"<<pay_file->paydate;
        pay_insert(pay_file,_carname,pay_file->carid);
        pay_file=(payinfo*)malloc(sizeof(payinfo));}
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp2);

    QApplication a(argc, argv);

    MainWindow w;
    addcar add_car;
    updatecar up_car;
    addsale add_sale;
    upsale up_sale;
    addpay add_pay;
    uppay up_pay;

    QObject::connect(&w,SIGNAL(showaddcar()),&add_car,SLOT(on_addcar_signal1()));
    QObject::connect(&add_car,SIGNAL(resetmain_car()),&w,SLOT(reset_car()));
    QObject::connect(&w,SIGNAL(showupcar()),&up_car,SLOT(on_upcar_signal1()));
    QObject::connect(&up_car,SIGNAL(resetmain_car()),&w,SLOT(reset_car()));
    QObject::connect(&w,SIGNAL(showaddsale()),&add_sale,SLOT(on_addsale_signal1()));
    QObject::connect(&add_sale,SIGNAL(resetmain_sale()),&w,SLOT(reset_sale()));
    QObject::connect(&w,SIGNAL(showupsale()),&up_sale,SLOT(on_upsale_signal1()));
    QObject::connect(&up_sale,SIGNAL(resetmain_sale()),&w,SLOT(reset_sale()));
    QObject::connect(&w,SIGNAL(showaddpay()),&add_pay,SLOT(on_addpay_signal1()));
    QObject::connect(&add_pay,SIGNAL(resetmain_pay()),&w,SLOT(reset_pay()));
    QObject::connect(&w,SIGNAL(showuppay()),&up_pay,SLOT(on_uppay_signal1()));
    QObject::connect(&up_pay,SIGNAL(resetmain_pay()),&w,SLOT(reset_pay()));

    QObject::connect(&w,SIGNAL(quit()),&add_car,SLOT(quit()));
    QObject::connect(&w,SIGNAL(quit()),&up_car,SLOT(quit()));
    QObject::connect(&w,SIGNAL(quit()),&add_sale,SLOT(quit()));
    QObject::connect(&w,SIGNAL(quit()),&up_sale,SLOT(quit()));
    QObject::connect(&w,SIGNAL(quit()),&add_pay,SLOT(quit()));
    QObject::connect(&w,SIGNAL(quit()),&up_pay,SLOT(quit()));

    w.show();
    a.exec();
    fp1=fopen("./data_car","wb+");
    fp2=fopen("./data_sale","wb+");
    fp3=fopen("./data_pay","wb+");
    //写文件
    car_file=car_head;
    while(car_file->next!=NULL){
        qDebug()<<car_file->next->name<<"!!!!!!!!!!!";
        fwrite(car_file->next,size1,1, fp1);
        sale_file=car_file->next->sale_head;
        while(sale_file->next!=NULL){
            qDebug()<<sale_file->next->carname<<"!"<<sale_file->next->carid<<"!"<<sale_file->next->clientid;
            fwrite(sale_file->next,size2,1,fp2);
            pay_file=sale_file->next->pay_head;
            while(pay_file->next!=NULL){
                qDebug()<<pay_file->next->carid<<"!"<<pay_file->next->paydate;
                fwrite(pay_file->next,size3,1,fp3);
                fwrite(car_file->next->name,sizeof(_carname),1,fp3);
                pay_file=pay_file->next;
            }
            sale_file=sale_file->next;
        }
        car_file=car_file->next;
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp2);
    return 0;
}

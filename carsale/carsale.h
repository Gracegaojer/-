#ifndef CARINFO_H
#define CARINFO_H
struct payinfo{
    char carid[20];
    char paydate[12];
    float paid_thistime;//交款金额
    float left_bill;//未支付
    char opname[20];//收款人
    payinfo* next;
};

struct saleinfo{
    char carid[20];
    char carname[20];
    char carcolor[10];
    char saledate[12];
    char clientname[20];
    char clientid[20];
    char clientphone[15];
    float saleprice;
    bool paidall;//0-有欠款；1-交完；
    saleinfo* next;
    payinfo* pay_head;
    payinfo* pay_trail;
};

typedef struct car_info{
    char name[20];
    int weight;
    int seatnum;
    int length;
    int wide;
    int height;
    int salenum;//saleinfo的数目；
    float salemoney;//销售款额
    car_info* next;
    saleinfo* sale_head;
    saleinfo* sale_trail;
}carinfo;

carinfo * car_create(char name[20],int weight,int seatnum,int length,int wide,int height);
int car_insert(carinfo* p);
int car_delete(char name[20]);
carinfo * car_update(char name[20],int weight=0,int seatnum=0,int length=0,int wide=0,int height=0);

saleinfo * sale_create(char carid[20],char carname[20],char carcolor[10],char saledate[12],char clientname[20],char clientid[18],char clientphone[11],float saleprice);
int sale_insert(saleinfo* p,char carname[20]);
int sale_delete(char carid[20],char carname[20]);
saleinfo * sale_update(char carid[20],char carname[20],char carcolor[10],char saledate[12],char clientname[20],char clientid[18],char clientphone[11],float saleprice);

payinfo * pay_create(char carid[20],char paydate[12],float paid_thistime,float left_bill,char opname[20]);
int pay_insert(payinfo* p,char carname[],char carid[]);
int pay_delete(char carname[],char carid[],char paydate[]);
payinfo * pay_update(char carname[],char carid[20],char paydate[12],float paid_thistime,float left_bill,char opname[20]);
#endif // CARINFO_H

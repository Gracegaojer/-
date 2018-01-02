#include"carsale.h"
#include<malloc.h>
#include <string.h>
#include"qdebug.h"
extern carinfo * car_head;
extern carinfo * car_trail;

carinfo * car_create(char name[20],int weight,int seatnum,int length,int wide,int height){//创建车型
    carinfo* p=(carinfo*)malloc(sizeof(carinfo));
    strcpy(p->name,name);
    p->weight=weight;
    p->seatnum=seatnum;
    p->length=length;
    p->wide=wide;
    p->height=height;
    p->salenum=0;
    p->salemoney=0;

    return p;
}

int car_insert(carinfo* p){//插入车型记录
    car_trail->next=p;
    p->sale_head=(saleinfo*)malloc(sizeof(saleinfo));
    p->sale_head->next=NULL;
    p->sale_trail=p->sale_head;
    p->next=0;
    car_trail=car_trail->next;
    car_trail->next=0;
    return 0;
}

int car_delete(char name[20]){//删除车型记录
    carinfo* p=car_head;
    carinfo * s=car_head;
    //由于car_head是不存的，所以没必要判断
    while(p->next!=0){
        if(!strcmp(p->next->name,name)){//匹配的车辆
            s=p->next;
            p->next=p->next->next;
            free(s);
            break;
        }
        else{
            p=p->next;
        }
    }
    return 0;
    //不需要提示删除，因为是可视化删除
}

carinfo * car_update(char name[20],int weight,int seatnum,int length,int wide,int height){//修改车型记录
    carinfo * p=car_head;
    while(p!=NULL){
        if(!strcmp(p->name,name)){
            if(weight!=0){
                p->weight=weight;
            }
            if(seatnum!=0){
                p->seatnum=seatnum;
            }
            if(length!=0){
                p->length=length;
            }
            if(wide!=0){
                p->wide=wide;
            }
            if(height!=0){
                p->height=height;
            }
            break;
        }
        else{p=p->next;}
    }
    return p;
}

saleinfo * sale_create(char carid[20],char carname[20],char carcolor[10],char saledate[12],char clientname[20],
char clientid[18],char clientphone[11],float saleprice){//创建销售记录
    saleinfo *p=(saleinfo*)malloc(sizeof(saleinfo));
    strcpy(p->carid,carid);
    strcpy(p->carname,carname);
    strcpy(p->carcolor,carcolor);
    strcpy(p->saledate,saledate);
    strcpy(p->clientname,clientname);
    strcpy(p->clientid,clientid);
    strcpy(p->clientphone,clientphone);
    p->saleprice=saleprice;
    return p;
}

int sale_insert(saleinfo* p,char carname[20]){//插入销售记录
    carinfo * car=car_head;
    while(car!=0){
        if(!strcmp(car->name,carname)){
            car->salenum++;
            car->salemoney+=p->saleprice;
            car->sale_trail->next=p;
            car->sale_trail=p;
            p->next=NULL;
            p->pay_head=(payinfo*)malloc(sizeof(payinfo));
            p->pay_head->next=NULL;
            p->pay_trail=p->pay_head;
            break;
        }
        else{
            car=car->next;
        }
    }
    return 0;
}

int sale_delete(char carid[20],char carname[20]){//删除销售记录
    car_info* p=car_head;
    saleinfo* s,*t;
    while(p!=NULL){
        if(!strcmp(p->name,carname)){
            s=p->sale_head;
            while(s->next!=NULL){
                if(strcmp(s->next->carid,carid)==0){
                    p->salemoney=p->salemoney-s->next->saleprice;//修改销售额
                    p->salenum--;//修改销量
                    t=s->next;
                    s->next=t->next;
                    free(t);
                    break;
                }
                else{s=s->next;}
            }
            break;
        }
        else{p=p->next;}
    }
    return 0;
}

saleinfo * sale_update(char carid[20],char carname[20],char carcolor[10],char saledate[12],char clientname[20],
char clientid[18],char clientphone[11],float saleprice){//修改销售记录
    carinfo* p=car_head;
    saleinfo* s;
    while(p!=NULL){
        if(strcmp(p->name,carname)==0){
            break;
        }
        else{p=p->next;}
    }
    s=p->sale_head;
    while(s->next!=NULL){
        if(strcmp(s->next->carid,carid)==0){
            s=s->next;
            strcpy(s->carid,carid);
            strcpy(s->carname,carname);
            strcpy(s->carcolor,carcolor);
            strcpy(s->saledate,saledate);
            strcpy(s->clientname,clientname);
            strcpy(s->clientid,clientid);
            strcpy(s->clientphone,clientphone);
            if(s->saleprice!=saleprice){
                p->salemoney=p->salemoney-s->saleprice+saleprice;
                s->saleprice=saleprice;
            }
            break;
        }
        else{s=s->next;}
    }
    return s;
}

payinfo * pay_create(char carid[20],char paydate[12],float paid_thistime,float left_bill,char opname[20]){//创建支付记录
    payinfo* p=(payinfo*)malloc(sizeof(payinfo));
    strcpy(p->carid,carid);
    strcpy(p->paydate,paydate);
    p->paid_thistime=paid_thistime;
    p->left_bill=left_bill;
    strcpy(p->opname,opname);
    return p;
}

int pay_insert(payinfo* p,char carname[],char carid[]){//插入支付记录
    carinfo * c=car_head;
    saleinfo * s;
    while(c->next!=NULL){
        if(strcmp(c->next->name,carname)==0){
            s=c->next->sale_head;
            while(s->next!=NULL){
                if(strcmp(s->next->carid,carid)==0){
                    if(p->left_bill==0) s->next->paidall=1;//记录已经缴费
                    s->next->pay_trail->next=p;
                    s->next->pay_trail=p;
                    p->next=NULL;
                    break;
                }
                s=s->next;
            }
            break;
        }
        c=c->next;
    }
    return 0;
}

int pay_delete(char carname[],char carid[],char paydate[]){//删除支付记录
    carinfo * c=car_head;
    saleinfo * s;
    payinfo * a,*b;
    while(c->next!=NULL){
        if(strcmp(c->next->name,carname)==0){
            s=c->next->sale_head;
            while(s->next!=NULL){
                if(strcmp(s->next->carid,carid)==0){
                    a=s->next->pay_head;
                    while(a->next!=NULL){
                        if(strcmp(a->next->paydate,paydate)==0){
                            b=a->next;
                            if(b->left_bill==0||a->left_bill!=0) s->next->paidall=0;
                            if(b->next!=NULL){
                                a->next=b->next;
                            }
                            else{
                                a->next=NULL;
                            }
                            free(b);
                            break;
                        }
                        a=a->next;
                    }
                    break;
                }
                s=s->next;
            }
            break;
        }
        c=c->next;
    }
    return 0;
}

payinfo * pay_update(char carname[],char carid[20],char paydate[12],float paid_thistime,float left_bill,char opname[20]){//修改支付记录
    carinfo * c=car_head;
    saleinfo * s;
    payinfo * a;
    while(c->next!=NULL){
        if(strcmp(c->next->name,carname)==0){
            s=c->next->sale_head;
            while(s->next!=NULL){
                if(strcmp(s->next->carid,carid)==0){
                    a=s->next->pay_head;
                    while(a->next!=NULL){
                        if(strcmp(a->next->paydate,paydate)==0){
                           //qDebug()<<c->next->name<<"||"<<s->next->carid<<"||"<<a->next->paydate;
                            if(!(a->next->left_bill)^!(left_bill==1)){//将float转化为int类型
                                s->next->paidall=!s->next->paidall;
                            }
                            a->next->paid_thistime=paid_thistime;
                            a->next->left_bill=left_bill;
                            strcpy(a->next->opname,opname);
                            break;
                        }
                        a=a->next;
                    }
                    break;
                }
                s=s->next;
            }
            break;
        }
        c=c->next;
    }
    return a;
}

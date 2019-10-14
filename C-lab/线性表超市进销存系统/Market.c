//
// Created by messi-lp on 18-10-14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[12];
    char name[20];
    int  num;
    int price;
    int point;

} merchandise;

typedef struct {
    char name[20];
    char id[20];
    int money;
    merchandise m;
    int num;
    float changeMoney;
    float discount;
    int pointNum;
    int alipay;
} member;

typedef struct {
    char  dealNUm[10];
    int  cashierNum;
    int  machineNum;
    char time[20];
    merchandise m;
    member man;


} receipt;

typedef struct SqList
{
    merchandise  *elem;
    int  length;
    int  listsize;
    int  increamentsize;
} SqList;


void wrongMessage(char *message);
void initList(merchandise *list,int *length);
void swap(merchandise *m1,merchandise *m2);
void store(const  merchandise*list,int length);
void qsort_wpy(merchandise*list,int left ,int right);
int find(char*id,merchandise*list,int length);
void insert(merchandise *list,merchandise m,int length);
void update(merchandise *list,int *length);
void delete(merchandise *list,int k,int *length);



void initList(merchandise *list,int *length){
    FILE *fp;
    merchandise temp;
    for (int j = 0; j <12 ; ++j) {
        temp.id[j]=0;
    }
    int i=0;
    fp=fopen("marketList.txt","r");
    if(fp==NULL)
        wrongMessage("打开文件失败,文件可能不存在");
    while (fscanf(fp,"%s%s%d%d%d",temp.id,temp.name,&temp.num,&temp.price,&temp.point)!=EOF) {
        list[i]=temp;
        i++;

    }
    *length=i;
    fclose(fp);
}
void swap(merchandise *m1,merchandise *m2){
    merchandise temp;
    temp=*m1;
    *m1=*m2;
    *m2=temp;
}


int ListEmpty(SqList list){
    if(list.length!=0){
        return 1;
    } else
        return 0;
}


void getElem(SqList list,int locate,merchandise* e){
    if (locate<1||locate>100)return;
    *e=list.elem[locate-1];
}

void store(const  merchandise*list,int length){
    FILE *fp;
    fp=fopen("marketList.txt","w");
    if (fp==NULL){
        wrongMessage("储存失败，无法创建或覆盖文件");
    }
    for (int i = 0; i <length ; ++i) {
        merchandise temp=list[i];

        fprintf(fp,"%s %s %d %d %d\n",temp.id,temp.name,temp.num,temp.price,temp.point);
    }
    fclose(fp);
}
void qsort_wpy(merchandise*list,int left ,int right){
    int l,r;
    l=left;
    r=right;
    merchandise k=list[left];
    if (left>=right)return;
    while (left<right){
        while (strcmp(list[right].id,k.id)>0&&right>left)right--;
        if (right>left) {
            list[right]=list[left++];
        }
        while(strcmp(list[left].id,k.id)<0&&right>left)left++;
        if (left<right) {
            list[left]=list[right--];
        }

    }
    list[left]=k;
    qsort_wpy(list,l,left-1);
    qsort_wpy(list,left+1,r);

}
void wrongMessage(char*message){
    printf("%s\n",message);
    exit(-1);
};
int find(char*id,merchandise*list,int length){
    int i=0;
    int j=length-1;
    int k=0;
    while (i<j){
        k=((i+j)/2);
        if (strcmp(id,list[k].id)>0)
            i=k+1;
        else if(strcmp(id,list[k].id)<0)
            j=k-1;
        else{
            return k;
        }


    }
    return 0;

}
void insert(merchandise *list,merchandise m,int length){
    int i=0;
    int index=length-1;
    while (i<length-1 && strcmp(m.id,list[i].id)>0)i++;
    while (index>=i){
        list[index+1]=list[index];
        index--;
    }
    list[i]=m;
}
void delete(merchandise *list,int k,int *length){
    for (int i = k; i < *length-1; ++i) {
        list[k]=list[k+1];
    }
    *length=*length-1;
}
void update(merchandise *list,int *length){
    int k=0;
    int i=2;
    int num=0;
    int len=*length;
    char  flag;
    merchandise temp;
    for (int l = 0; l <12 ; ++l) {
        temp.id[l]=0;
    }
    printf("what do you want ? \n");
    printf("a----->increase something\n");
    printf("b----->increase something new or change something\n");
    printf("c----->delete something\n");
    printf("q----->exit\n");
    scanf("%c",&flag);
    fflush(stdin);
    while (flag!='q') {
        switch (flag) {
            case 'a': {
                printf("please input id and num\n");
                scanf("%s%d",temp.id,&temp.num);
                k=find(temp.id,list,*length);
                if (k)
                    list[k].num+=temp.num;
                else
                    printf("id not find\n");
                break;
            }
            case 'b':{
                printf("please input name id price num point\n ");
                scanf("%s%s%d%d%d", temp.name,temp.id,&temp.price,&temp.num,&temp.point);
                insert(list,temp,*length);
                *length=len+1;
                break;
            }
            case 'c':{
                printf("input delete id\n");
                scanf("%s%d",temp.id,&temp.num);
                k=find(temp.id,list,*length);
                if (k)
                    delete(list,k,length);

                else
                    printf("id not find\n");
                break;
            }
            default:{
                printf("please input correct char!");
            }
        }
        printf("what do you want ? \n");
        printf("a----->increase something\n");
        printf("b----->increase something new or change something\n");
        printf("c----->delete something\n");
        printf("q----->exit\n");
        scanf("%c",&flag);
        fflush(stdin);

    }
    printf("how many?");
    scanf("%d",&i);
    printf("please input name id price num point\n ");
    for (int j = 0; j < i; ++j) {
        scanf("%s%s%d%d%d", temp.name,temp.id,&temp.price,&temp.num,&temp.point);
        k=find(temp.id,list,*length);
        if (k){
            list[k]=temp;
        } else{
            insert(list,temp,*length);
            *length=len+1;

        }

    }

}

void sell(merchandise*list,int length,member *man){
    int isMember;
    int k;
    printf("do you have member num?\n1---->yes ,0---->no\n");
    scanf("%d",&isMember);
    if (isMember){
        printf("please input your member id\n");
        scanf("%s",man->id);
    } else{
        strcpy(man->id,"0");
    }
    printf("input the id of merchandise.\n");
    scanf("%s",man->m.id);
    printf("input num\n");
    scanf("%d",&man->num);
    printf("input your money\n");
    scanf("%d",&man->money);

    while (!(k=find(man->id,list,length))){
        printf("wrong id\n");
        scanf("%s",man->m.id);
    }
        list[k].num-=man->num;
        if (list[k].num<0){
            printf("No more merchandise\n");
            return;
        }
        man->m=list[k];

    if (!strcmp(man->id,"0")){
        man->discount=1;
    } else{
        man->discount=0.9;
    }

    man->changeMoney=man->money-(man->num*man->m.price*man->discount);
    man->pointNum+=man->m.point*man->num;

}




void printReceipt(member m){
        receipt r;
        r.man=m;
        r.cashierNum=1;
        strcpy(r.dealNUm,"20181011");
        strcpy(r.time,"20181017");
        r.m=m.m;
        printf("交易号：%s\n",r.dealNUm);
        printf("收银员号：%d\n机号：%d\n",r.cashierNum,r.machineNum);
        printf("商品序号:%s\n商品名称:%s\n数量：%d   单价：%d\n",r.m.id,r.m.name,r.man.num,r.m.price);
        printf("应收金额:%d\n",r.m.price*r.man.num);
        printf("实收金额:%d   找零金额:%f\n",r.man.money,r.man.changeMoney);
        if (strcpy(r.man.id,"0")!=0)
            printf("会员号：%s   会员积分:%d\n",r.man.id,r.man.pointNum);
        else
            printf("没有会员\n");
}
merchandise list[100];
int main(){
    int length=0;
    char flag;
    member mam;
    initList(list,&length);
    qsort_wpy(list,0,length-1);
    for (int i = 0; i <length ; ++i) {
        printf("%s   %s\n",list[i].id,list[i].name);
    }
    printf("请选择功能\n");
    printf("a----->进货\nb----->出售\nc----->打印小票\nq----->退出\n");
    scanf("%c",&flag);
    fflush(stdin);
    while (flag!='q'){
        switch (flag){
            case 'a':{
                update(list,&length);
                break;
            }
            case 'b':{
                sell(list,length,&mam);
                break;
            }
            case 'c':{
                printReceipt(mam);
                break;
            }
            default: {
                printf("请输入正确的选项\n");
                break;
            }
        }
        printf("a----->进货\nb----->出售\nc----->打印小票\nq----->退出\n");
        scanf("%c",&flag);
        fflush(stdin);


    }


    store(list,length);

}
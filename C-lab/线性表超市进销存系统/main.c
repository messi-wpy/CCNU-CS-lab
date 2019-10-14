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

typedef struct LNode{
    merchandise data;
    struct LNode *next;

}LNode;


LNode* initList();
void purchase();
void wrongMessage(char *message);





void wrongMessage(char*message){
    printf("%s\n",message);
    exit(-1);
};
/*
 * 12344 苹果 10 5 1
32411 梨 5 9 1
42345 葡萄 3 4 2
34235 牛奶 3 4 5
 */

LNode* initList(){
    FILE *fp;
    LNode *head=(LNode*)malloc(sizeof(LNode));
    LNode*trail,*pnew;

    merchandise temp;

    head->next=NULL;
    trail=head;
    fp=fopen("marketList.txt","r");
    if(fp==NULL)
        wrongMessage("打开文件失败,文件可能不存在");
    while (fscanf(fp,"%s%s%d%d%d",temp.id,temp.name,&temp.num,&temp.price,&temp.point)!=EOF) {
        pnew = (LNode *) malloc(sizeof(LNode));
        if (pnew == NULL)
            wrongMessage("分配内存失败");
        pnew->data = temp;
        trail->next = pnew;
        pnew->next = NULL;
        trail = pnew;
    }
    fclose(fp);
    return head;

}
void swapNum(int *a,int *b){
    int temp;
    temp=*b;
    *b=*a;
    *a=temp;

}
void swap(LNode*l1,LNode*l2){
    char temp_1[20];
    strcpy(temp_1,l1->data.id);
    strcpy(l1->data.id,l2->data.id);
    strcpy(l2->data.id,temp_1);
    strcpy(temp_1,l1->data.name);
    strcpy(l1->data.name,l2->data.name);
    strcpy(l2->data.name,temp_1);
    swapNum(&l1->data.price,&l2->data.price);
    swapNum(&l1->data.point,&l2->data.point);
    swapNum(&l1->data.num,&l2->data.num);
}


void swap_2(LNode*low,LNode*high){
    LNode *temp;
    LNode *temp2 = high->next->next;
    temp = low->next;
    low->next = high->next;
    high->next->next = temp->next;
    high->next = temp;
    high->next->next = temp2;
}

void sort_slist(LNode*phead,LNode*pend){

    if(phead == NULL || pend == NULL) return;
    if(phead == pend) return;
    LNode* pslow = phead;
    LNode* pfast = phead->next;
    LNode* ptemp = phead;

    char key[12]={0};
    strcpy( key,phead->data.id);
    while (pfast && pfast != pend->next) {
        if (strcmp(pfast->data.id, key) < 0) {
            ptemp = pslow;
            pslow = pslow->next;
            swap(pslow, pfast);
        }
        pfast = pfast->next;
    }
    swap(phead, pslow);
    sort_slist(phead, ptemp);
    sort_slist(pslow->next, pend);
}


//进货
void purchase(LNode*list){
    LNode* pnew=(LNode*)malloc(sizeof(merchandise));
    printf("please in");
    while (){


    }

}
//销售
void sell(){


}
//储存
void store(LNode* list){
    LNode *head=list;
    FILE *fp;
    fp=fopen("marketList.txt","w");
    if (fp==NULL){
        wrongMessage("储存失败，无法创建或覆盖文件");
    }
    while (head->next!=NULL){
        merchandise temp=head->next->data;
        fprintf(fp,"%s %s %d %d %d\n",temp.id,temp.name,temp.num,temp.price,temp.point);
        head=head->next;
    }
    fclose(fp);

}
void destroyList(LNode *list){
    LNode *p,*q;
    p=list;
    while (p->next!=NULL){
        q=p->next;
        p->next=q->next;
        free(q);

    }
    free(list);

}

int main() {
    LNode *list;
    LNode *end;
    LNode*p;

    merchandise temp;
    list=initList();
    p=list;
    end=list;
   while (end->next!=NULL)end=end->next;

   sort_slist(list->next,end);
    while (p->next!=NULL)
    {
        printf("%s  %s\n",p->next->data.id,p->next->data.name);
        p=p->next;

    }

    printf("success");
    store(list);
    destroyList(list);


    return 0;
}
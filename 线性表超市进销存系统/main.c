#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char id[10];
    char name[10];
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
        wrongMessage("打开文件失败");
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
//进货
void purchase(merchandise*list){


}
//销售
void sell(){


}
//储存
void store(){}
void destoryList(LNode *list){
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
    LNode *p;
    FILE *fp;
    int  a;
    merchandise temp;
   p=initList();
   list=p;

    while (list->next!=NULL)
    {
        printf("%s  %s\n",list->next->data.id,list->next->data.name);
        list=list->next;

    }
    destoryList(p);


    return 0;
}
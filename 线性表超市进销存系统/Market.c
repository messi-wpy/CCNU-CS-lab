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
void purchase();
void wrongMessage(char *message);
void initList(merchandise *list,int *length){
    FILE *fp;
    merchandise temp;
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
    if (left==right||left>right)return;
    while (left<right){
        while (strcmp(list[right].id,k.id)>0&&right>left)right--;
        if (right>left) {
            list[right]=list[left++];
        }
        while(strcmp(list[left].id,k.id)>0&&right>left)left++;
        if (left<right) {
            list[left]=list[right--];
        }

    }
    list[left]=k;
    qsort_wpy(list,l,left);
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
        k=(i+j/2);
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
    while (i<length && strcmp(m.id,list[i].id)>0)i++;
    while (index>=i){
        list[index+1]=list[index];
        index--;
    }
    list[i]=m;
}
void purchase(merchandise *list,int *length){
    int k=0;
    merchandise temp;
    printf("please inout name id price num point\n ");
    while (scanf("%s%s%d%d%d", temp.name,temp.id,&temp.price,&temp.num,&temp.point) != EOF) {
        k=find(temp.id,list,*length);
        if (k){
            list[k]=temp;
        } else{
            insert(list,temp,*length);
            *length=(*length)++;

        }

    }

}
merchandise list[100];
int main(){
    int length=0;
    initList(list,&length);
    qsort_wpy(list,0,length-1);
    for (int i = 0; i <length ; ++i) {
        printf("%s   %s\n",list[i].id,list[i].name);
    }

}
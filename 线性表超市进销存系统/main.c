#include <stdio.h>
#include <stdlib.h>
#include "market.h"



void wrongMessage(char*message){
    printf("%s\n",message);
    exit(-1);
};
void initList(){


}
void purchase(merchandise*list){


}

int main() {
    FILE *fp;
    int a;
    float  b;
    fp=fopen("marketList.txt","r");
    if(fp==NULL) {
        wrongMessage("打开文件失败");
    }
    fscanf(fp,"%d%f",&a,&b);
    printf("%d   %f",a,b);
    fclose(fp);
    printf("Hello, World!\n");
    return 0;
}
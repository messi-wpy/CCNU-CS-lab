#include <iostream>
#include <stack>
#include <string.h>
using namespace std;
typedef char ElemType;
//顺序存储链表
typedef struct SqList
{
    ElemType  *elem;
    int  length;
    int  listsize;
    int  increamentsize;
} SqList;

//链试存储链表
typedef struct LNode{
    ElemType data;
    struct LNode *next;

}LNode,* LinkList;

//2-1
void reverse(int * arrays,int length){
    int i=length-1;
    for (int k = 0; k <length/2 ; ++k) {
        int temp= arrays[k];
        arrays[k]=arrays[i];
        arrays[i--]=temp;

    }

}

//2-2
void  insert(LinkList list,LinkList node){
    node->next=list->next;
    list->next=node;

}

//2-3
void input(LinkList q,int *length){
    int i=0;
    int len=0;
    LinkList trail=q;
    while (i!=-1){
        scanf("%d",&i);
        LinkList node=(LinkList)malloc(sizeof(LNode));
        node->data=i;
        trail->next=node;
        trail=trail->next;
        len++;
    }
    trail->next=NULL;
    *length=len;
}

//2-4
void insertLetter(LinkList list, char letter){
    if (list==NULL)return;
    if (list->next==NULL){
        LinkList node=(LinkList)malloc(sizeof(LNode));
        node->data=letter;
        list->next=node;
        return;
    }
    while (list->next!=NULL && list->next->data < letter)
        list=list->next;
    LinkList  l=(LinkList)malloc(sizeof(LNode));
    l->data=letter;
    l->next=list->next;
    list->next=l;


}

void delete_letter(LinkList list, char letter){
    if (list==NULL||list->next==NULL)return;
    while (list->next!=NULL && list->next->data != letter)
        list=list->next;
    if (list->next->data==letter) {
        LinkList p = list->next;
        list->next = list->next->next;
        free(p);
    } else
        return;

}

//3-1
int correct(const char *exp,int *tag,int length){
    stack <char >s;
    *tag=1;
    for (int i = 0; i < length; ++i) {
        if (exp[i]=='(') {
            s.push('(');
            continue;
        }
        else if(exp[i]=='{') {
            s.push('{');
            continue;
        }
        else if (exp[i]=='[') {
            s.push('[');
            continue;
        }
        else if (exp[i]==')'){
            if(s.top() != '('){
                *tag=0;
                return 0;
            }
            s.pop();
            continue;
        }
        else if (exp[i]=='}'){
            if(s.top() !='{'){
                *tag=0;
                return 0;
            }
            s.pop();
            continue;
        }
        else if (exp[i]==']'){
            if(s.top()!='['){
                *tag=0;
                return 0;
            }
            s.pop();
            continue;
        } else
            continue;

    }
    return 1;

}


//3-2

int*squ;
int front, rear;
int length;
int flag;
int * initqueue(int m){
    squ=(int *)malloc(sizeof(int)*m);
    front=rear=0;
    length=m;
    flag=0;
    if (squ==NULL)
        exit(-1);
    return squ;

}
int isEmpty(){
    return rear==front;

};
int  isFull() {
    return ((rear+1)%length)==front;
}

int getRear() {
    if (isEmpty())return  -1;
    int k=(rear-1+length)%length;
    return squ[k] ;
}
int getFront() {
    if (isEmpty())return -1;
    return squ[front];
}
int  insertFront(int value) {
    if (isFull())return 0;

    front=(front-1+length)%length;
    squ[front]=value;
    return 1;
}

//3-3
int isHuiWen(){
    char words[100];
    int i=0;
    int j=0;
    char w;
    scanf("%c",&w);
    while (w!='@'){
        words[j++]=w;
        scanf("%c",&w);

    }
    j=j-1;
    while (i<=j){
        if (words[i++]!=words[j--])
            return 0;

    }
    return 1;

}



//4&5-1
int Replace(char *s,char*t, char *v){
    if (strlen(s)<strlen(t))return 0;
    int i=strlen(s);
    int  j=strlen(t);
    int k=strlen(v);
    int h=0;
    int n=0;
    int index=0;
    char result[80]={'\0'};
    char sub[10];
    while (h<=i-j){
        strncpy(sub,s+h,j);
        sub[j]='\0';
        if (strcmp(sub,t)==0){
            strcat(result,v);
            h+=j;
            index+=k;
            n++;
            continue;
        } else{
            result[index++]=s[h];
            h++;
        }
    }
    while (h<i) {
        result[index++] = s[h++];
    }
   for (int x=0;x<index;x++)
       s[x]=result[x];
    return n;



}

//4&5-2
void invertedString(char *string,int l,int r){
    if (l>=r)
        return;
    char temp;
    temp=string[l];
    string[l]=string[r];
    string[r]=temp;
    invertedString(string,l+1,r-1);

}

/*4&5-3
 * 空间　１；
 * 交换次数o(n)
*/
void  shiftringth(int *num,int length,int r){
    int dis=r%length;
    int res=num[0];
    int index=0;
    int p=0;
    for (int j = 1; j <=r; ++j) {
        if(length%j==0&&r%j==0)
            p=j;
    }

    for (int i = 0; i < p; ++i) {
        index=i;
        res=num[i];
        do {
            int temp = num[(index + dis) % length];
            num[(index + dis) % length] = res;
            res = temp;
            index = (index + dis) % length;
        }while (index!=i);

    }


}

//第九章排序9-1
void insertionSorting(LinkList head){
    if(head==NULL||head->next==NULL)return;
    LinkList node=head;
    while (node->next!=NULL){
        LinkList n=node->next;

        LinkList  tempHead=head;
        while (tempHead->next !=n && tempHead->next->data < n->data)
            tempHead=tempHead->next;
        if (tempHead->next==n){
            node=node->next;
            continue;
        }
        node->next=n->next;
        n->next=tempHead->next;
        tempHead->next=n;

    }

}


/*第九章 9-2
 * 要求：
 * 先对较短
 * 记录<=3,不再分割
 */

int Partition(int a[],int left,int right){
    int key=a[left];
    while(left<right){
        while (left<right && a[right]>=key) right--;
            a[left]=a[right];
        while (left<right && a[left]<=key) left++;
            a[right]=a[left];
    }

    a[left]=key;
    return left;

}

void quickSort(int *nums,int length){
    if (length<=1)
        return;
    int low=0;
    int key=0;
    int high=length-1;
    stack<int >stack;
    stack.push(low);
    stack.push(high);
    while (!stack.empty()){
        high=stack.top();
        stack.pop();
        low=stack.top();
        stack.pop();
        key=Partition(nums,low,high);
        if (key-1>low){
            stack.push(low);
            stack.push(key-1);

        }
        if (key+1<high){
            stack.push(key+1);
            stack.push(high);
        }


    }


}
//9-3
/*
void hashsort(int a[]){
    int b[10000];
    for (int i = 0; i < 1000; ++i) {
        for (int j = a[i]; b[j] ; (j+1)%10000) {
            b[j]=a[i];
        }
    }

    for (int i = 0,j=0; i <1000 ; ++j) {
        if (b[j]){
            for (int x = b[j],k=j; b[k]; k=(k+1)%10000) {
                if (b[k]==x){
                    a[i++]=x;
                    b[k]=0;
                }
                }
            }
    }

}
*/
//9-4中值记录
int findMid(int nums[],int length){
    int l=(length-1)>>1;
    for (int i = 0; i <= l; ++i) {
        int j=i;
        for (int k = i+1; k < length; ++k) {
            if (nums[j]<nums[k])
                j=k;
        }
        if (j!=i) {
            int temp = nums[i];
            nums[i] =nums[j];
            nums[j]=temp;
        }
    }
    return nums[l];

}


int main() {
    int a []={1,2,3,4,5,6,7};
    //reverse(a,7);
  /*  std::cout << "Hello, World!" << std::endl;
    for (int i = 0; i <7 ; ++i) {
        cout<<a[i]<<"       ";
    }*/


   /* LNode head;
    int length=3;
    LinkList list=&head;
    list=(LinkList)malloc(sizeof(LNode));
    list->data='h';
    insertLetter(list,'a');
    insertLetter(list,'b');
    insertLetter(list,'f');
    insertLetter(list,'d');
    delete_letter(list,'b');

    */


  /*  for (int j = 0; j <length ; ++j) {
        cout<<list->next->data<<"  ";
        list=list->next;
    }
    cout<<length;*/

    char *words="(){}[](sad){(asd)}";
    int  flag=0;
   // correct(words,&flag,18);
    //cout<<flag<<endl;

    //if (isHuiWen())
      //  cout<<"right";



      /*initqueue(6);
      insertFront(2);
      insertFront(4);
      insertFront(3);
      insertFront(5);
      cout<<getFront()<<"   "<<getRear()<<endl;
    */
      char dest[100]={'a','b','c','d','g','h','a','b','e','e','r','\0'};

   //   printf("%s\n",dest);

    //  int n=Replace(dest,"abc","wangpenyu");


   // invertedString(dest,0,10);
    //printf("%s  \n",dest);

   // int shift[]={1,2,3,4,5,6};
   // shiftringth(shift,6,3);
  /*  for (int i = 0; i < 6; ++i) {
        printf("%d\n",shift[i]);
    }*/


   /* LNode h,l1,l2,l3,l4,l5;
    l1.data=3;
    h.next=&l1;
    l2.data=6;
    l1.next=&l2;
    l3.data=1;
    l2.next=&l3;
    l4.data=5;
    l3.next=&l4;
    l5.data=0;
    l4.next=&l5;
    l5.next=NULL;
    insertionSorting(&h);
    for (int j = 0; j <5 ; ++j) {
        printf("%d\n",h.next->data);
        h=*h.next;
    }
*/
    int asd []={2,6,7,3,7,3,4,1,0,48,9};
    //quickSort(asd,12);
    //for (int i = 0; i <12 ; ++i) {
      //  printf("%d\n",asd[i]);
    //}

    printf("%d\n",findMid(asd,11));
       return 0;
}
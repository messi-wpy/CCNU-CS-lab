#include <iostream>

using namespace std;

class student{
private:
    int index;
    int s;
public:
    student(int x=0,int S=0){
        index=x;
        s=S;
    }
    int getIndex(){
        return index;
    }
    bool numberOff(int S){
        if(s==S){
            cout<<index;
            index=0;
            return true;
        }
        return false;
    }
};

class CircleList{
private:
    int size;
    int index;

public:
    CircleList(int size,int index){
        this->size=size;
        this->index=index;
    }
    int getSize(){
        return size;
    }
    void setSize(int size){
        this->size=size;
    }
    void setIndex(int index){
        this->index=index;
    }
    int getIndex(){
        return index;
    }
    int getNext(){
        int temp=index%size;
        index++;
        if (temp!=0)
            return temp;
        else
            return  size;
    }
};
student stu[100];

int main()
{
    int size,w,s;
    cout<<"input size,w,s";
    cin>>size>>w>>s;
    for(int i=1;i<=size;i++){
        stu[i]=student(i,s);
    }
    CircleList circle(size,w);
    int x=1;
    while(size!=0){
        int  index=circle.getNext();
        if(stu[index].getIndex()==0)continue;
        if(stu[index].numberOff(x)){
            x=1;
            size--;
        }else
            x++;
    }
    return 0;
}

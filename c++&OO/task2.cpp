#include <iostream>
#define PI 3.141592654
using namespace std;
class Circle{
private:
    double r;
public:
    Circle (double R=0){
        r=R;
    }
    double getR(){
        return r;
    }


};
double sum(Circle circleArray[],int size ){
    double sum=0;
    for(int i=0;i<size;i++){
        double r=circleArray[i].getR();
        sum+=r*r*PI;
    }
    return sum;

}
Circle circleArray[100];
int main()
{
    int size;
    cout<<"enter size:";
    cin>>size;
    cout<<"enter r of the circle:";
    for(int i=0;i<size;i++){
        double r;
        cin>>r;
        circleArray[i]=Circle(r);
    }
    cout<<"sum="<<sum(circleArray,size);

    return 0;
}



#include <iostream>
#include<math.h>
#include<iomanip>
using namespace std;

int main()
{
    float a,b,c;
    cin>>a>>b>>c;
    if(b*b==4*a*c)
        cout<<setprecision(5)<<"x1=x2="<<(-b+sqrt(b*b-4*a*c))/(2*a)<<endl;
    else if(b*b>4*a*c){
        cout<<setprecision(5)<<"x1="<<(-b+sqrt(b*b-4*a*c))/(2*a)<<endl;
        cout<<setprecision(5)<<"x2="<<(-b-sqrt(b*b-4*a*c))/(2*a)<<endl;
    }
    else{
        float real=-b/(2*a);
        float virtualNum=sqrt(4*a*c-b*b)/(2*a);
        cout<<"x1="<<real<<"+"<<virtualNum<<"i"<<endl;
        cout<<"x2="<<real<<"-"<<virtualNum<<"i"<<endl;
    }
    return 0;
}

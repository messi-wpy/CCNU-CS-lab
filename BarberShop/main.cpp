#include <iostream>
#include <queue>
#include <cstdlib>
#include <time.h>

using namespace std;
class customer{
public:
    int costTime;
    int endtime;
    int enterTime;
    int barber;
    bool ishaircut;
    customer(int a,int b,int num,bool haircut){
        this->costTime=a;
        enterTime=b;
        this->barber=num;
        this->ishaircut=haircut;
        endtime=0;
    }
    bool operator <(const customer&a)const {
        return a.endtime<endtime;

    }

};
class barber{
public:
    int money;
    int price;
    int num;
    barber(){
        money=0;
        num=0;
    }
    barber(int price){
        this->price=price;
    }
    void work(){
        money+=price;

    }


};
class BarberShop{
public:
    int set;
    int money;
    int totalTime;
    int currentTime;
    BarberShop(int set,int totalTime){
        this->set=set;
        money=0;
        this->totalTime=totalTime;
        currentTime=0;
    }



};
/**
 *@author wpy
 * 两个队列，一个不同队列来排序进入的顾客，先来后到
 * 一个优先队列，理发店有n个椅子，可以同时进行理发，所以谁的结束时间最早谁先出队列，用优先队列
 * 全局维护一个currentime，表示当前时间，如果优先队列里的顾客结束时间早于当前时间，就出队列，算钱
 * 最后当currentime > 关店时间时，清空一排队的和正在理发的，不再进入新顾客
 * currentime由顾客入店间隔时间来推动。
 */
int main() {
    BarberShop shop(3,720);
    barber barbers[3];
    barbers[0].price=40;
    barbers[1].price=30;
    barbers[2].price=20;
    srand((unsigned)time(nullptr));

    int lastTime;
    //出门事件
    queue<customer*>sets;
    priority_queue<customer*>out;
    customer *c=new customer(rand()%40+10,rand()%30+5,rand()%3,true);
    shop.currentTime+=c->enterTime;
    c->endtime=c->costTime+shop.currentTime;
    sets.push(c);

    while(!sets.empty()||(!out.empty())){
        if (!out.empty()) {
            customer *temp = out.top();
            while (shop.currentTime > temp->endtime) {
                out.pop();
                barbers[temp->barber].work();
                delete temp;
                temp = out.top();
            }
        }
            customer *nc=new customer(rand()%40+5,rand()%30+3,rand()%3,true);
            shop.currentTime+=nc->enterTime;
            nc->endtime=shop.currentTime+nc->costTime;
            if(shop.currentTime<shop.totalTime){
                    sets.push(nc);
                    while (!sets.empty()&&out.size()<3){
                        out.push(sets.front());
                        sets.pop();
                    }

            } else{
                while (!sets.empty()){
                    customer *last=sets.front();
                    sets.pop();
                    barbers[last->barber].work();

                }
                while (!out.empty()){
                    customer *last=out.top();
                    out.pop();
                    barbers[last->barber].work();
                }

            }


    }

    for (int i = 0; i <shop.set ; ++i) {
        shop.money+=barbers[i].money;
    }
    cout<<"Barber shop business volume:"<<shop.money<<" RMB"<<endl;
    cout<<"barber A grade "<<barbers[0].money<<" RMB"<<endl;
    cout<<"barber B grade "<<barbers[1].money<<" RMB"<<endl;
    cout<<"barber C grade "<<barbers[2].money<<" RMB"<<endl;


    return 0;
}


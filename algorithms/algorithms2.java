package leetcode;


/**
 * 回溯算法求解0/1背包问题
 *
 */
public class algorithms2 {

    int n=7;
    int capacity=150;
    int weight[]={35,30,60,50,40,10,25};
    int value[]={10,40,30,50,35,40,30};
    int maxValue=0;
    int currentValue=0;
    int currentWeight=0;
    int []order=new int[n];
    int []bestWay=new int[n];


    public static void main(String[] args) {
        algorithms2 a=new algorithms2();
        a.backTracking(0);
        for (int i = 0; i <a.n ; i++) {
            System.out.print(a.bestWay[i]+"  ");

        }
        System.out.println();
        System.out.println(a.maxValue);
    }

    public void backTracking(int t){


        //剪枝
        if (currentWeight>capacity) {
            return;

        }
        if (t>n-1){
            if (currentValue>maxValue){
                maxValue=currentValue;
                for (int i = 0; i <n ; i++) {
                    bestWay[i]=order[i];
                }
            }
            return;
        }

            //左子树,是否装入
            currentWeight+=weight[t];
            currentValue+=value[t];
            order[t]=1;
            backTracking(t+1);

            //回溯,右子树,不装入
            currentWeight-=weight[t];
            currentValue-=value[t];
            order[t]=0;
            backTracking(t+1);
        }


}

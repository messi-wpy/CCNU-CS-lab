package OperatingSystem;

public class TimeUtil {

    public static String timeFormat(int time){
        int h=time/100;
        int m=time%100;
        StringBuilder sb=new StringBuilder();

        if (h<10)
            sb.append(0);
        sb.append(h).append(":");
        if (m<10)
            sb.append(0);
        sb.append(m);
        return sb.toString();
    }
    public static int timeSub(int time1,int time2){
        int h1=time1/100,h2=time2/100;
        int m1=time1%100,m2=time2%100;

        int resH=h2-h1;
        int resM=m2-m1;
        return resH*60+resM;

    }
    public static int timeSubCost(int time,int cost){
        int h=time/100;
        int m=time%100;
        int resH=h-(cost-m+60)/60;
        int resM=(cost-m+60)%60;
        return resH*100+resM;
    }
    public static int  timeAdd(int time1,int cost){
        int h1=time1/100;
        int m1=time1%100;
        int resH=h1+(m1+cost)/60;
        int resM=(m1+cost)%60;
        return resH*100+resM;
    }

}

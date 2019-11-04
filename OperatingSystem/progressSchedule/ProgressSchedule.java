package OperatingSystem.progressSchedule;

import java.util.*;

public class ProgressSchedule {


    public static void main(String[] args) {
        List<Progress>list=new ArrayList<>();
        int n=0;
        Scanner sc=new Scanner(System.in);
        n=sc.nextInt();
        while (n>0){
            n--;
            Progress p=new Progress(sc.nextInt(),sc.nextInt(),sc.nextInt(),sc.nextInt());
            list.add(p);

        }
        ProgressSchedule schedule=new ProgressSchedule();
        schedule.FIFO(list);
        schedule.timeRotation(list);
    }

    /**
      * 先进先出调度算法
      * @param list
     *  假设每次就绪状态中出队列, 阻塞队列中队首的进程转换成就绪状态
     */
    public void FIFO(List<Progress>list){
        int time=0;
        int waitTime=0;
        Deque<Progress>readyQueue=new LinkedList<>();
        Deque<Progress>blockingQueue=new LinkedList<>();

        for (int i = 0; i <list.size() ; i++) {
            Progress temp=list.get(i);
            if (temp.getStatus()== Progress.Status.READY)
                readyQueue.add(temp);
            if (temp.getStatus()== Progress.Status.WAIT)
                blockingQueue.add(temp);
        }
        while (!readyQueue.isEmpty()||!blockingQueue.isEmpty()){

            Progress out=readyQueue.poll();
            if (out==null){
                out=blockingQueue.poll();
            }
            if (out==null)
                break;
            print(out,time);
            waitTime+=time;
            time+=out.getCost();
            readyQueue.add(blockingQueue.poll());

        }
        System.out.println("平均等待时间： "+(double)waitTime/list.size());

    }


    /**
     * 时间轮转算法
     */
    public void timeRotation(List<Progress>list){
        Deque<Progress>deque=new LinkedList<>();
        deque.addAll(list);
        int slice=10;
        int time=0;
        int allCost=0;
        while (!deque.isEmpty()){
            Progress temp=deque.poll();
            int remain=temp.getCost()-slice;
            if (remain<=0){
                time+=temp.getCost();
                print(temp,time-temp.time);
                allCost+=time-temp.time;
                continue;
            }
            time+=slice;
            temp.setCost(remain);
            deque.add(temp);

        }
        System.out.println("平均等待时间： "+(double)allCost/list.size());


    }


    private void print(Progress p,int waitTime){
        System.out.println(String.format(Locale.CHINA,"进程id：%d     等待时间%d",p.getPid(),waitTime));

    }

}

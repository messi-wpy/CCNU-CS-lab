package OperatingSystem.progressSchedule;

import OperatingSystem.TimeUtil;
import sun.net.ProgressEvent;

import java.util.*;

public class ProgressSchedule {


    //默认开始的启动时间为8:00
    private int startTime=800;
    private int slice=0;
    private PriorityQueue<Progress>progressQueue;
    private PriorityQueue<Progress>readyQueue;
    private PriorityQueue<Progress>blockingQueue;
    private PriorityQueue<Progress>priorityQueue;
    public ProgressSchedule(int slice){
        this.slice=slice;
        progressQueue=new PriorityQueue<>(new Comparator<Progress>() {
            @Override
            public int compare(Progress o1, Progress o2) {

                return o1.getEnterTime()-o2.getEnterTime();
            }
        });

        readyQueue=new PriorityQueue<>(new Comparator<Progress>() {
            @Override
            public int compare(Progress o1, Progress o2) {
                return o1.getEnterTime()-o2.getEnterTime();
            }
        });
        blockingQueue=new PriorityQueue<>(new Comparator<Progress>() {
            @Override
            public int compare(Progress o1, Progress o2) {
                return o1.getReadyTime()-o2.getReadyTime();
            }
        });

        priorityQueue=new PriorityQueue<>(new Comparator<Progress>() {
            @Override
            public int compare(Progress o1, Progress o2) {
                return o2.getPriorityNum()-o1.getPriorityNum();
            }
        });

    }
    public static void main(String[] args) {
        List<Progress>list=new ArrayList<>();


        ProgressSchedule schedule=new ProgressSchedule(10);
        schedule.FIFO();
        schedule.timeRotation();
        schedule.prioritySchedule();
    }

    public void myInput(PriorityQueue<Progress>queue){
        startTime=800;
        queue.add(new Progress(1,40,0,1,800,0));
        queue.add(new Progress(2,30,0,1,809,0));
        queue.add(new Progress(3,15,1,10,820,830));
        queue.add(new Progress(4,40,1,2,915,930));
        queue.add(new Progress(5,35,0,1,920,0));
        queue.add(new Progress(6,10,1,3,930,950));
        queue.add(new Progress(7,35,0,3,935,0));

    }
    /**
      * 先进先出调度算fa
     *  假设每次就绪状态中出队列, 阻塞队列中队首的进程转换成就绪状态
     */

    private void getNextReadyProgress(){
        while (!progressQueue.isEmpty()&&progressQueue.peek().getEnterTime()<=startTime){
            Progress temp=progressQueue.peek();
            progressQueue.poll();
            if (temp.getStatus() == Progress.Status.READY)
                readyQueue.add(temp);
            if (temp.getStatus() == Progress.Status.WAIT)
                blockingQueue.add(temp);
        }

        while (!blockingQueue.isEmpty()&&blockingQueue.peek().getReadyTime()<=startTime){
            Progress p=blockingQueue.poll();
            p.setEnterTime(p.getReadyTime());
            readyQueue.add(p);
        }
        if (readyQueue.isEmpty()&&priorityQueue.isEmpty()){
            int nextTime=Integer.MAX_VALUE;
            Progress p1,p2;
            p1=progressQueue.peek();
            p2=blockingQueue.peek();
            if (p2!=null){
                nextTime=p2.getReadyTime();
            }
            if (p1!=null) {
                nextTime=Math.min(p1.getEnterTime(),nextTime);
            }
            run(null,startTime,nextTime);
            startTime=nextTime;
        }
    }

    /**
     * 先入先出调度算法
     */
    public void FIFO(){
        System.out.println("----先入先出调度算法----- ");
        int waitTime=0;
        int n=0;
        myInput(progressQueue);
        n=progressQueue.size();
        while (!progressQueue.isEmpty()||!readyQueue.isEmpty()||!blockingQueue.isEmpty()){
            Progress cur=null;
            //获取下一个任务
            getNextReadyProgress();
            if (readyQueue.isEmpty()){
                continue;
            }
            //run progress
            cur=readyQueue.poll();
            int endtime=TimeUtil.timeAdd(startTime,cur.getCost());
            run(cur,startTime,endtime);
            waitTime+=TimeUtil.timeSub(cur.getEnterTime(),startTime);
            startTime=endtime;
        }
        System.out.println("平均等待时间： "+(double)waitTime/n);

    }


    /**
     * 时间轮转算法
     */
    public void timeRotation(){
        System.out.println("------时间轮转算法-----");
        int allCost=0;
        myInput(progressQueue);
        int n=progressQueue.size();
        while (!progressQueue.isEmpty()||!readyQueue.isEmpty()||!blockingQueue.isEmpty()){
            Progress cur=null;
            getNextReadyProgress();

            if (readyQueue.isEmpty()){
                continue;
            }
            cur=readyQueue.poll();
            int remain=cur.getCost()-slice;
            if (remain<=0){
                int endTime=TimeUtil.timeAdd(startTime,cur.getCost());
                run(cur,startTime,endTime);
                startTime=endTime;
                allCost+=TimeUtil.timeSub(cur.originEnterTime,TimeUtil.timeSubCost(endTime,cur.originCostTime));
                continue;
            }
            int endTime=TimeUtil.timeAdd(startTime,slice);
            run(cur,startTime,endTime);
            startTime=endTime;
            cur.setCost(remain);
            cur.setEnterTime(endTime);
            readyQueue.add(cur);
        }

        System.out.println("平均等待时间： "+(double)allCost/n);


    }

    /**
     * 优先数调度算法
     */
    public void prioritySchedule(){
        System.out.println("----优先数调度算法-----");
        int all=0;
        myInput(progressQueue);
        int n=progressQueue.size();
        while (!priorityQueue.isEmpty()||!progressQueue.isEmpty()||!readyQueue.isEmpty()||!blockingQueue.isEmpty()){
            Progress cur=null;
            getNextReadyProgress();
            while (!readyQueue.isEmpty()){
                priorityQueue.add(readyQueue.poll());
            }
            if (priorityQueue.isEmpty()){
                continue;
            }
            cur=priorityQueue.poll();
            int endTime=TimeUtil.timeAdd(startTime,cur.getCost());
            run(cur,startTime,endTime);
            all+=TimeUtil.timeSub(cur.getEnterTime(),startTime);
            startTime=endTime;

        }
        System.out.println("平均等待时间： "+all/n);

    }

    private void run(Progress p,int form,int to){

        System.out.println(String.format(Locale.CHINA,"%s----%s cpu运行 进程id： %s",TimeUtil.timeFormat(form)
                ,TimeUtil.timeFormat(to),p==null?"空闲(无就绪进程)":String.valueOf(p.getPid())));
    }

    private void print(Progress p,int waitTime){
        System.out.println(String.format(Locale.CHINA,"进程id：%d     等待时间%d",p.getPid(),waitTime));

    }

    public int getStartTime() {
        return startTime;
    }

    public void setStartTime(int startTime) {
        this.startTime = startTime;
    }
}

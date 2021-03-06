package OperatingSystem.JobSchedule;

import java.util.*;

import static OperatingSystem.TimeUtil.*;

public class JobScheduling {


    public static void main(String[] args) {

        PriorityQueue<Job>queue1=new PriorityQueue<>(new Comparator<Job>() {
            @Override
            public int compare(Job o1, Job o2) {
                return o1.getTime()-o2.getTime();
            }
        });

        PriorityQueue<Job>queue2=new PriorityQueue<>(new Comparator<Job>() {
            @Override
            public int compare(Job o1, Job o2) {
                return o1.getTime()-o2.getTime();
            }
        });

        PriorityQueue<Job>queue3=new PriorityQueue<>(new Comparator<Job>() {
            @Override
            public int compare(Job o1, Job o2) {
                return o1.getTime()-o2.getTime();
            }
        });


        Scanner in =new Scanner(System.in);
        int n=0;
        n=in.nextInt();
        for (int i = 0; i <n ; i++) {
            Job job=new Job(in.nextInt(),in.nextInt(),in.nextInt());
            queue1.add(job);
            queue2.add(job);
            queue3.add(job);
        }
        System.out.println("FIFO先入先出算法:");
        FIFOMethods(queue1);
        System.out.println("------------------------------");
        System.out.println("短作业优先算法:");
        shortWorkMethods(queue2);
        System.out.println("------------------------------");
        System.out.println("最高响应比优先作业调度算法:");
        highestResponseMethods(queue3);
    }

    //FIFO先入先出调度算法
    public static void FIFOMethods(Queue<Job>queue){
        int startTime=queue.peek().getTime();

        while (!queue.isEmpty()){
            Job temp=queue.poll();
            jobOut(temp,timeFormat(startTime));
            startTime=timeAdd(startTime,temp.getCost());
        }
    }


    //短作业优先算法
    public static void shortWorkMethods(Queue<Job>queue){
        PriorityQueue<Job>waitQueue=new PriorityQueue<>(new Comparator<Job>() {
            @Override
            public int compare(Job o1, Job o2) {
                return o1.getCost()-o2.getCost();
            }
        });
        Job first =queue.poll();
        int startTime=first.getTime();
        int endTime=timeAdd(startTime,first.getCost());
        jobOut(first,timeFormat(startTime));
        while (!queue.isEmpty()){
            while (!queue.isEmpty()&&queue.peek().getTime()<=endTime) {
                waitQueue.add(queue.poll());
            }
            startTime=endTime;
            Job out =waitQueue.poll();
            endTime=timeAdd(startTime,out.getCost());
            jobOut(out,timeFormat(startTime));
        }

        while (!waitQueue.isEmpty()){
            startTime=endTime;
            Job out =waitQueue.poll();
            endTime=timeAdd(startTime,out.getCost());
            jobOut(out,timeFormat(startTime));


        }
    }

    //最高响应比优先作业调度算法.
    public static void  highestResponseMethods(Queue<Job>queue){

        Job first =queue.poll();
        int startTime=first.getTime();
        int endTime=timeAdd(startTime,first.getCost());
        jobOut(first,timeFormat(startTime));
        List<Job>waitList=new ArrayList<>();
        while (!queue.isEmpty()||!waitList.isEmpty()){

            while (!queue.isEmpty()&&queue.peek().getTime()<=endTime) {
                waitList.add(queue.poll());
            }

            startTime=endTime;
            int maxIndex=0;
            float maxRate=Float.MIN_VALUE;
            for (int i = 0; i <waitList.size() ; i++) {
                Job job=waitList.get(i);
                job.setWaitTime(timeSub(job.getTime(),endTime));
                float rate=(float)job.getWaitTime()/job.getCost();
                if (rate>maxRate){
                    maxRate=rate;
                    maxIndex=i;
                }
            }
            Job out =waitList.remove(maxIndex);
            endTime=timeAdd(startTime,out.getCost());
            jobOut(out,timeFormat(startTime));
        }




    }





    public static void jobOut(Job job,String time){
        System.out.println("作业序号："+job.getNum()+"\t进入内存时间："+time+"\t花费时间： "+job.getCost()+"(min)");
    }
}

package OperatingSystem.PartitionedStorageManagement;

import java.util.*;

public class StorageManagement {

    private LinkedList<Partition>freeAreaTable;
    private LinkedList<Partition>allocatedTable;

    public StorageManagement(LinkedList<Partition> list){
        freeAreaTable=list;
        allocatedTable=new LinkedList<>();
    }

    //首次适应算法
    public void FirstAdaptation(List<Job>list) {
        System.out.println("首次适应算法");

        for (int i = 0; i < list.size(); i++) {
            Job job=list.get(i);
            Iterator<Partition> it=freeAreaTable.iterator();
            boolean isEnough=false;
            while (it.hasNext()){
                Partition partition=it.next();
                if (partition.length>=job.size){
                    isEnough=true;
                    if (partition.length==job.size){
                        it.remove();
                    }

                    Partition allocate=new Partition(partition.startAddress,job.size,"job"+job.num);
                    allocatedTable.add(allocate);
                    partition.length-=job.size;
                    partition.startAddress+=job.size;

                    break;

                }

            }
            if (!isEnough) {
                System.out.println("没有空闲区间能容纳任务 "+job.num);
                break;
            }
        }
        printOut();

    }


    //最佳适应算法
    public void OptimalAdaptation(List<Job>list){
        System.out.println("最佳适应算法");
        for (int i = 0; i < list.size(); i++) {
            Job job=list.get(i);
            Partition Optimal=null;
            Iterator<Partition>it=freeAreaTable.iterator();
            while (it.hasNext()){
                Partition partition=it.next();
                if (partition.length>=job.size){
                    if (partition.length==job.size){
                        Optimal=partition;
                        it.remove();
                        break;
                    }
                    if (Optimal==null||Optimal.length>partition.length){
                        Optimal=partition;
                    }

                }
            }
            if (Optimal==null){
                System.out.println("没有空闲区间能容纳任务 "+job.num);
                break;
            }
            allocatedTable.add(new Partition(Optimal.startAddress,job.size,"job"+job.num));
            Optimal.length-=job.size;
            Optimal.startAddress+=job.size;
        }
        printOut();

    }

    //最坏适应算法
    public void WorstAdaptation(List<Job>list){
        System.out.println("最坏适应算法");
        Comparator<Partition>comparable=new Comparator<Partition>() {
            @Override
            public int compare(Partition o1, Partition o2) {
                return o2.length-o1.length;
            }
        };

        boolean isEnough=true;

        for (int i = 0; i < list.size(); i++) {
            Job job=list.get(i);
            freeAreaTable.sort(comparable);
            Partition partition=freeAreaTable.getFirst();
            if (partition.length<job.size){
                System.out.println("没有空闲区间能容纳任务 "+job.num);
                break;
            }
            if (partition.length==job.size)
                freeAreaTable.removeFirst();


            allocatedTable.add(new Partition(partition.startAddress,job.size,"job"+job.num));
            partition.length-=job.size;
            partition.startAddress+=job.size;

        }
        printOut();




    }

    public void printOut(){
        System.out.println("空闲区表：");
        System.out.println("始址  长度  标志");
        freeAreaTable.forEach(System.out::println);
        System.out.println("已分配表:");
        System.out.println("始址  长度  标志");
        allocatedTable.forEach(System.out::println);
        System.out.println();
    }
}

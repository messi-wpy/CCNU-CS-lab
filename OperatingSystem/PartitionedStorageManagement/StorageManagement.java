package OperatingSystem.PartitionedStorageManagement;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

public class StorageManagement {

    private LinkedList<Partition>freeAreaTable;
    private LinkedList<Partition>allocatedTable;

    public StorageManagement(LinkedList<Partition> list){
        freeAreaTable=list;
        allocatedTable=new LinkedList<>();
    }

    //首次适应算法
    public void FirstAdaptation(List<Job>list) {
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
        System.out.println("首次适应算法");
        printOut();

    }



    public void printOut(){
        System.out.println("空闲区表：");
        System.out.println("始址  长度  标志");
        freeAreaTable.forEach(System.out::println);
        System.out.println("已分配表:");
        System.out.println("始址  长度  标志");
        allocatedTable.forEach(System.out::println);
    }
}

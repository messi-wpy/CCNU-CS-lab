package OperatingSystem.PartitionedStorageManagement;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Test {
    public static void main(String[] args) {
        List<Job>list=new ArrayList<>();
        list.add(new Job(1,12));
        list.add(new Job(2,30));
        list.add(new Job(3,28));


        LinkedList<Partition>freeTable=new LinkedList<>();
        freeTable.add(new Partition(100,35));
        freeTable.add(new Partition(156,12));
        freeTable.add(new Partition(200,28));

        StorageManagement management=new StorageManagement(freeTable);
        management.FirstAdaptation(list);


        LinkedList<Partition>freeTable2=new LinkedList<>();
        freeTable2.add(new Partition(100,35));
        freeTable2.add(new Partition(156,12));
        freeTable2.add(new Partition(200,28));

        StorageManagement management2=new StorageManagement(freeTable2);
        management2.OptimalAdaptation(list);

        LinkedList<Partition>freeTable3=new LinkedList<>();
        freeTable3.add(new Partition(100,35));
        freeTable3.add(new Partition(156,12));
        freeTable3.add(new Partition(200,28));

        StorageManagement management3=new StorageManagement(freeTable3);
        management3.WorstAdaptation(list);

    }

}

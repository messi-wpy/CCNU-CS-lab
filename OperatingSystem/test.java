package OperatingSystem;

import java.util.Comparator;
import java.util.PriorityQueue;

public class test {

    public static void main(String[] args) {
        PriorityQueue<Integer>queue=new PriorityQueue<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2-o1;
            }
        });
        queue.add(4);
        queue.add(2);
        queue.add(65);
        queue.add(22);
        while (!queue.isEmpty()){
            System.out.println(queue.poll());
        }
    }
}

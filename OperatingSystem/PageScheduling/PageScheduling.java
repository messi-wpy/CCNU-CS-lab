package OperatingSystem.PageScheduling;

import java.util.*;
import java.util.function.BiConsumer;

public class PageScheduling {

    //默认为3
    //表示空闲内存块数
    private int freeBlockNum;
    public PageScheduling(){
        this(3);
    }

    public PageScheduling(int freeNum){
        this.freeBlockNum=freeNum;
    }

    public static void main(String[] args) {
        int []pages={4  ,3  ,2  ,1  ,4  ,3 , 5 , 4  ,3  ,2  ,1 ,5};
        PageScheduling pageScheduling=new PageScheduling();
        pageScheduling.LRUps(pages);
    }
    //FIFO
    public void FIFOps(int []pages){
        HashSet<Integer>set=new HashSet<>();
        Deque<Integer>deque=new LinkedList<>();
        int missingNum=0;
        System.out.println("FIFO调度算法");
        for (int page:pages) {
            System.out.print(page+" ");
        }
        System.out.println();
        System.out.println("淘汰页面号：");
        for (int i = 0; i < pages.length; i++) {
            if (deque.size()<freeBlockNum){
                deque.offer(pages[i]);
                set.add(pages[i]);
                missingNum++;
                System.out.print("无 ");
            }else {
                if (set.contains(pages[i])){
                    System.out.print("无 ");
                }else {
                    missingNum++;
                    int out=deque.poll();
                    System.out.print(out+" ");
                    set.remove(out);
                    deque.offer(pages[i]);
                    set.add(pages[i]);
                }


            }

        }
        System.out.println();
        System.out.println(String.format(Locale.CHINA,"缺页总次数： %d 缺页中断率： %.2f",missingNum,(float)missingNum/pages.length));

    }

    //最近最少使用调度算法（LRU）
    public void LRUps(int []pages){
        HashMap<Integer,Integer>map=new HashMap<>();
        int missingNum=0;
        System.out.println("LRU调度算法");
        for (int page:pages) {
            System.out.print(page+" ");
        }
        System.out.println();
        System.out.println("淘汰页面号：");

        for (int i = 0; i < pages.length; i++) {
            if (map.containsKey(pages[i])){
                System.out.print("无 ");
                map.forEach(new BiConsumer<Integer, Integer>() {
                    @Override
                    public void accept(Integer integer, Integer integer2) {
                        map.put(integer,integer2+1);
                    }
                });
                map.put(pages[i],0);
            }else {
                missingNum++;
                if (map.size()<3){
                    map.put(pages[i],0);
                    System.out.print("无 ");
                    map.forEach(new BiConsumer<Integer, Integer>() {
                        @Override
                        public void accept(Integer integer, Integer integer2) {
                            map.put(integer,integer2+1);
                        }
                    });
                }else {
                    int max=-1;
                    int key=-1;
                    for (Map.Entry<Integer,Integer> entry:map.entrySet()) {
                        if (max<entry.getValue()){
                            key=entry.getKey();
                            max=entry.getValue();
                        }
                    }
                    System.out.print(key+" ");
                    map.remove(key);
                    map.forEach(new BiConsumer<Integer, Integer>() {
                        @Override
                        public void accept(Integer integer, Integer integer2) {
                            map.put(integer,integer2+1);
                        }
                    });
                    map.put(pages[i],0);


                }
            }
        }
        System.out.println();
        System.out.println(String.format(Locale.CHINA,"缺页总次数： %d 缺页中断率： %.2f",missingNum,(float)missingNum/pages.length));

    }


    private void swap(int []array,int a,int b){
        int temp=array[a];
        array[a]=array[b];
        array[b]=temp;
    }
}

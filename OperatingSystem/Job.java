package OperatingSystem;

public class Job {


    private int num;
    private int time;
    private int cost;
    private int waitTime;

    public Job(int num, int time, int cost) {
        this.num = num;
        this.time = time;
        this.cost = cost;
        waitTime=0;
    }

    public int getNum() {
        return num;
    }

    public void setNum(int num) {
        this.num = num;
    }

    public int getTime() {
        return time;
    }

    public void setTime(int time) {
        this.time = time;
    }

    public int getCost() {
        return cost;
    }

    public void setCost(int cost) {
        this.cost = cost;
    }

    @Override
    public String toString(){
        return new StringBuilder().append(num).append(time).append(cost).toString();

    }

    public int getWaitTime() {
        return waitTime;
    }

    public void setWaitTime(int waitTime) {
        this.waitTime = waitTime;
    }
}

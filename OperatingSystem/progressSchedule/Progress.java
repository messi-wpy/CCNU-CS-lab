package OperatingSystem.progressSchedule;

public class Progress {

    public enum Status{
        READY,WAIT,RUN
    }

    private int pid;
    private int cost;
    private Status status;
    private int PriorityNum;
    //固定一个进程消费的时间
    public int originCostTime;
    public int originEnterTime;
    private int enterTime;
    private int readyTime;


    public Progress(int pid, int cost, int status, int priorityNum,int enterTime,int readyTime) {
        this.pid = pid;
        this.cost = cost;
        originCostTime=cost;
        originEnterTime=enterTime;
        PriorityNum = priorityNum;
        this.enterTime=enterTime;
        this.readyTime=readyTime;
        if (status==0)
            this.status=Status.READY;
        else if (status==1) {
            this.status = Status.WAIT;
            originEnterTime=readyTime;
        }
        else
            this.status=Status.RUN;

    }

    public int getEnterTime() {
        return enterTime;
    }

    public void setEnterTime(int enterTime) {
        this.enterTime = enterTime;
    }

    public int getReadyTime() {
        return readyTime;
    }

    public void setReadyTime(int readyTime) {
        this.readyTime = readyTime;
    }

    public int getPid() {
        return pid;
    }

    public void setPid(int pid) {
        this.pid = pid;
    }

    public int getCost() {
        return cost;
    }

    public void setCost(int cost) {
        this.cost = cost;
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }

    public int getPriorityNum() {
        return PriorityNum;
    }

    public void setPriorityNum(int priorityNum) {
        PriorityNum = priorityNum;
    }
}

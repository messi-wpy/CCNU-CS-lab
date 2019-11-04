package OperatingSystem.progressSchedule;

public class Progress {

    public enum Status{
        READY,WAIT,RUN
    }

    private int pid;
    private int cost;
    private Status status;
    private int PriorityNum;
    public int time;

    public Progress(int pid, int cost, int status, int priorityNum) {
        this.pid = pid;
        this.cost = cost;
        time=cost;
        PriorityNum = priorityNum;
        if (status==0)
            this.status=Status.READY;
        else if (status==1)
            this.status=Status.WAIT;
        else
            this.status=Status.RUN;

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

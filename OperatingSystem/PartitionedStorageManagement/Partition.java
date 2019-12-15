package OperatingSystem.PartitionedStorageManagement;

public class Partition {
    //一块分区的信息
    public int startAddress;
    public int length;
    public String name;

    public Partition(int startAddress, int length) {
        this(startAddress,length,"未分配");
    }

    public Partition(int startAddress, int length, String name) {
        this.startAddress = startAddress;
        this.length = length;
        this.name = name;
    }

    @Override
    public String toString(){
        StringBuilder sb=new StringBuilder();
        sb.append(startAddress).append('k').append("  ")
                .append(length).append('k').append("  ")
                .append(name);
        return sb.toString();
    }
}

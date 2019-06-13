package leetcode;


import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * 贪心法
 * 哈夫曼树编码
 *
 * 证明哈夫曼树满足最优子结构性质
 *
 * 由哈夫曼树的构建过程可知，wi, wj 所在结点是兄弟结点（在不影响阅读的
 * 前提下，以wi, wj 指代这两个结点）。假设在哈夫曼树中，wi, wj 所在结点
 * 的深度不是最深的，则哈夫曼树应似图1 样式，存在一些结点，其深度大于wi
 * , wj 的深度。在图1中，wi, wj的父结点V的权重应大于结点X权重，否则构建
 * 哈夫曼树时，应选择V而不是X作为U的子结点。但这是不可能的，因为由假设知
 * wi, wj是W中权重最小的两个元素。得出矛盾，问题得证。
 *
 */
public class algorithms4 {
    public static class Node {
        char c;
        int weight;
        Node left,right;
    }

    public static void main(String[] args) {
        algorithms4 a=new algorithms4();
    }

    /**
     * 按照贪心算法每次找权值最小（即值最小）的两个数，构成孩子结点，
     * 并将这两个数据排除出这一堆数据之外
     *
     * 由于哈弗曼树的数据全在叶子结点，所以把上述权值最小的两个数据构
     * 成父结点，然后再将父结点的权值放回上述数据，返回第一步，重复上
     * 述过程，直到所有的数据都变成哈夫曼树的叶子结点
     *
     */
    public Node createHuffman(Node[] nodes){
        PriorityQueue<Node>queue=new PriorityQueue<>(nodes.length, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                return o2.weight-o1.weight;
            }
        });

        queue.addAll(Arrays.asList(nodes));

        Node head=null;
        while (!queue.isEmpty()){
            Node node1=queue.poll();
            Node node2=queue.poll();
            if (node2==null){
                head=node1;
                break;
            }
            Node node=new Node();
            node.weight=node1.weight+node2.weight;
            node.left=node1;
            node.right=node2;
            queue.add(node);
            head=node;

        }

        return head;

    }

    public void getEndecode(Node head){
        endecode(head,"");
    }
    public void endecode(Node node,String code){
        if (node==null)
            return;
        if (node.left==null&&node.right==null){
            System.out.println("符号："+node.c+"  编码："+code);
        }
        endecode(node.left,code+"0");
        endecode(node.right,code+"1");

    }



}

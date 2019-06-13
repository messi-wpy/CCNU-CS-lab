package leetcode;

/**
 * 最大字段和问题
 * 蛮力法  分治法  动态规划法实现
 * 测试数据：
 * int[] test={-2,11,-4,13,-5,-2};
 * 结果：20
 */
public class algorithms3 {

    public static void main(String[] args) {
        int[] test={-2,11,-4,13,-5,-2};
        algorithms3 a=new algorithms3();
        System.out.println(a.getMaxSub_1(test));
        System.out.println(a.getMaxSub_2(test));
        System.out.println(a.getMaxSub_3(test));
    }
    //蛮力法实现 O(n^2)
    public int getMaxSub_1(int [] nums){
        int max=Integer.MIN_VALUE;
        for (int i = 0; i <nums.length ; i++) {
            int temp=0;
            for (int j = i; j <nums.length ; j++) {
                temp+=nums[j];
                max=Math.max(temp,max);
            }
        }
        return max;
    }

    //分治法  O(nlogn)
    public int getMaxSub_2(int [] nums){
        return divideAndConquer(nums,0,nums.length-1);
    }

    public int divideAndConquer(int [] nums,int start,int end){
        if (start==end)
            return nums[start];

        int mid =(end-start)/2+start;
        int left=divideAndConquer(nums,start,mid);
        int right=divideAndConquer(nums,mid+1,end);

        int midMax=0;
        int temp=0;
        int maxleft=0;
        for (int i = mid; i >=start ; i--) {
            temp+=nums[i];
            maxleft=Math.max(temp,maxleft);
        }
        int temp2=0;
        int maxRight=0;
        for (int i = mid+1; i <=end ; i++) {
            temp2+=nums[i];
            maxRight=Math.max(temp2,maxRight);

        }
        midMax=maxRight+maxleft;
        int subMax=left>right?left:right;
        return subMax>midMax?subMax:midMax;
    }

    //动态规划 O(n)
    public int getMaxSub_3(int[] nums){
        int sum,temp;
        sum=temp=0;
        for (int i = 0; i < nums.length; i++) {
            if (temp>0){
                temp+=nums[i];
            }else{
                temp=nums[i];

            }
            if (temp>sum){
                sum=temp;
            }

        }
        return sum;

    }

}

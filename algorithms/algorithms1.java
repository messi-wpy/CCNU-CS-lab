package leetcode;

/**
 * @auth wpy
 *
 * 实验一：字符串匹配
 * 分析 BF,KMP,BM 算法区别时间复杂度
 */
public class algorithms1 {
    public static void main(String[] args) {
        bF("asghjababsdabasgababsdabadasdababsdaba","ababsdaba");
        kmp("asghjababsdabasgababsdabadasdababsdaba","ababsdaba");
    }
    //蛮力法,BF
    public  static void bF (String text,String pattern){
        int index=0;
        int i,j;
        i=j=0;
        while (i<text.length()){
            if (text.charAt(i)==pattern.charAt(j)){
                i++;
                j++;
            }
            else {
                index++;
                i=index;
                j=0;
                continue;

            }
            if (j==pattern.length()){
                j=0;
                System.out.println(index);

            }


        }
    }


    //kmp改进算法
    //next数组求法
    public static void  makeNext(int next[],String pattern){

        int j = 0;
        int k = -1;
        int len = pattern.length();
        next[0] = -1;

        while (j < len - 1) {
            if (k == -1 || pattern.charAt(k) == pattern.charAt(j)) {

                j++;
                k++;
                next[j] = k;
            } else {
                k = next[k];
            }
        }
    }
    //kmp
    public static void kmp(String s,String pattern){
        int i = 0;
        int j = 0;
        int slen = s.length();
        int plen = pattern.length();

        int[] next = new int[plen];

        makeNext( next,pattern);

        while (i < slen && j < plen) {

            if (s.charAt(i) == pattern.charAt(j)) {
                i++;
                j++;
            } else {
                if (next[j] == -1) {
                    i++;
                    j = 0;
                } else {
                    j = next[j];
                }

            }

            if (j == plen) {
                System.out.println(i-j);
                j=0;
            }
        }
    }


    //BM(Boyer-Moore)算法实现：
    public static int match(String s, String pattern){


        int moduleSuffix = pattern.length() -1;
        int module_index = moduleSuffix;
        int origin_index = moduleSuffix;

        for(int ot = origin_index; origin_index < s.length() && module_index >= 0;){
            char oc = s.charAt(origin_index);
            char mc = pattern.charAt(module_index);
            if(oc  == mc){
                origin_index--;
                module_index--;
            }else{
                // 坏字符规则
                int badMove = badCharacter(pattern,oc,module_index);
                // 好字符规则
                int goodMove = goodCharacter(pattern,module_index);
                origin_index = ot + Math.max(badMove, goodMove);
                module_index = moduleSuffix;
                // ot就是中间变量
                ot = origin_index;
            }
        }

        if(module_index < 0){
            // 多减了一次
            return origin_index + 1;
        }

        return -1;
    }
    public static int badCharacter(String moduleString, char badChar,int badCharSuffix){
        return badCharSuffix - moduleString.lastIndexOf(badChar, badCharSuffix);
    }

    /**
     * 利用好后缀规则计算移动位数
     */
    public static int goodCharacter(String moduleString,int goodCharSuffix){
        int result = -1;
        // 模式串长度
        int moduleLength = moduleString.length();
        // 好字符数
        int goodCharNum = moduleLength -1 - goodCharSuffix;

        for(;goodCharNum > 0; goodCharNum--){
            String endSection = moduleString.substring(moduleLength - goodCharNum, moduleLength);
            String startSection = moduleString.substring(0, goodCharNum);
            if(startSection.equals(endSection)){
                result = moduleLength - goodCharNum;
            }
        }

        return result;
    }




}

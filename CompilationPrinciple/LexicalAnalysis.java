package CompilationPrinciple;

import com.sun.org.apache.bcel.internal.generic.NEW;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

public class LexicalAnalysis {
    private String input;
    private int index;
    private static HashSet<String>mainWords=new HashSet<>(Arrays.asList("begin","if","then","while","do","end"));
    private static HashMap<String,Integer>speciesCode=new HashMap<>();
    static
    {
        speciesCode.put("begin",1);
        speciesCode.put("if",2);
        speciesCode.put("then",3);

    }
    public LexicalAnalysis(String s){
        input=s;
        index=0;
    }
    private void initTable(){


    }
    public boolean isLetter(char a){
        return a>='a'&&a<='z'||a>='A'&&a<='Z';
    }
    public boolean isDigit(char a){
        return a>='0'&&a<='9';
    }

    public String getWord(){
        char ch=input.charAt(index);
        if ()

    }

    //去掉空格等其他不必要的字符
    public void getbc(){
        char temp=input.charAt(index);
        while (temp==' '||temp=='\n'){
            index++;
            temp=input.charAt(index);
        }
    }
    public void startAnalysis(){



    }










}

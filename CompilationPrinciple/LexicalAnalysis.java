package CompilationPrinciple;

import com.sun.org.apache.bcel.internal.generic.NEW;

import java.io.*;
import java.util.*;

public class LexicalAnalysis {
    private String input;
    private int index;
    private boolean isFromFile=false;
    private File sourceFile;
    private static HashSet<String>mainWords=new HashSet<>(Arrays.asList("begin","if","then","while","do","end"));
    private static HashMap<String,Integer>speciesCode=new HashMap<>();
    static
    {
        speciesCode.put("begin",1);
        speciesCode.put("if",2);
        speciesCode.put("then",3);
        speciesCode.put("while",4);
        speciesCode.put("do",5);
        speciesCode.put("end",6);
        speciesCode.put("+",13);
        speciesCode.put("-",14);
        speciesCode.put("*",15);
        speciesCode.put("/",16);
        speciesCode.put(":",17);
        speciesCode.put(":=",18);
        speciesCode.put("<",20);
        speciesCode.put("<>",21);
        speciesCode.put("<=",22);
        speciesCode.put(">",23);
        speciesCode.put(">=",24);
        speciesCode.put("=",25);
        speciesCode.put(";",26);
        speciesCode.put("(",27);
        speciesCode.put(")",28);
        speciesCode.put("#",0);

        // TODO: 2019/10/16 补全
    }
    public LexicalAnalysis(String s){
        input=s;
        index=0;
    }
    public LexicalAnalysis(File file){
        sourceFile=file;
        isFromFile=true;
    }
    public boolean isLetter(char a){
        return a>='a'&&a<='z'||a>='A'&&a<='Z';
    }
    public boolean isDigit(char a){
        return a>='0'&&a<='9';
    }

    /**
     *
     * @return String[]:数组：第一个数代表该word的大种类：
     * “1”-->单词，可能是关键词
     * “2”-->数字
     * “3”-->标识符
     * 第二个表示获得的word
     */
    private String[] getWord(){
        getbc();
        String[]res=new String[2];
        if (index>=input.length())
            return null;
        char ch=input.charAt(index);
        StringBuilder builder=new StringBuilder();
        if (isLetter(ch)){
            res[0]="1";
            //识别正规式： letter(letter|digit)*
            while (isLetter(ch)||isDigit(ch)){
                builder.append(ch);
                index++;
                if (index>=input.length())
                    break;
                ch=input.charAt(index);
            }
        }else if (isDigit(ch)){
            //识别数字
            res[0]="2";
            while (isDigit(ch)){
                builder.append(ch);
                index++;
                if (index>=input.length())
                    break;
                ch=input.charAt(index++);
            }


        }else {
            res[0]="3";
            //识别分隔符等符号
            while (!isDigit(ch)&&!isLetter(ch)&&ch!=' '){
                builder.append(ch);
                if (builder.length()>=2){
                    if (!speciesCode.containsKey(builder.toString())){
                        builder.deleteCharAt(builder.length()-1);
                        index--;
                        break;

                    }

                }
                index++;
                if (index>=input.length())
                    break;
                ch=input.charAt(index++);
            }


        }
        res[1]=builder.toString();
        return res;
    }

    //去掉空格等其他不必要的字符
    public void getbc(){
        if (index>=input.length())
            return;
        char temp=input.charAt(index);
        while (temp==' '||temp=='\n'){
            index++;
            if (index>=input.length())
                return;
            temp=input.charAt(index);
        }
    }

    private String getFromFile(){
        FileInputStream in =null;
        StringBuilder sb=null;
        try {
            in=new FileInputStream(sourceFile);
            BufferedReader reader=new BufferedReader(new InputStreamReader(in));
            sb=new StringBuilder();
            String line=reader.readLine();
            while (line!=null){
                sb.append(line);
                line=reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            try {
                in.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return sb.toString();
    }
    public void startAnalysis(){
        if (isFromFile){
            input=getFromFile();
        }

        while (index<input.length()){
            String[]words=getWord();
            if (words==null)
                break;
            if (words[0].equals("1")){
                if (mainWords.contains(words[1])){
                    print(words[1],speciesCode.get(words[1]));
                }else
                    print(words[1],10);

            }else if (words[0].equals("2")){
                print(words[1],11);
            }else {
                if (speciesCode.containsKey(words[1])){
                    print(words[1],speciesCode.get(words[1]));
                }else {
                    throw new IllegalStateException("wrong word: "+words[1]);
                }

            }


        }


    }


    public void print(String word,int code){
        if (code==10)
            System.out.println(String.format(Locale.ENGLISH,"(%d,'%s')  ",code,word));
        else
            System.out.println(String.format(Locale.ENGLISH,"(%d,%s)  ",code,word));
    }








}

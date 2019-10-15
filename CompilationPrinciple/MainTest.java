package CompilationPrinciple;

import java.io.*;
import java.util.Scanner;

public class MainTest {

    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        char[] input=new char[255];

        FileInputStream in =null;
        StringBuilder sb=null;
        try {
            in=new FileInputStream("./src/main/java/CompilationPrinciple/test");
            BufferedReader reader=new BufferedReader(new InputStreamReader(in));
            sb=new StringBuilder();
            String line=reader.readLine();
            while (line!=null){
                sb.append(line);
                line=reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(sb.toString());





    }


}

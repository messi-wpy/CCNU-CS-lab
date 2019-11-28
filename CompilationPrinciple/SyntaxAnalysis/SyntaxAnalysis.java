package CompilationPrinciple.SyntaxAnalysis;

import CompilationPrinciple.LexicalAnalysis;

public class SyntaxAnalysis {

    private LexicalAnalysis lexical;
    private int syn = -1;
    private int kk = 0;
    private String[] word = null;

    public static void main(String[] args) {
        SyntaxAnalysis analysis=new SyntaxAnalysis(new LexicalAnalysis("x:=a+b*c end#"));
        //SyntaxAnalysis analysis=new SyntaxAnalysis(new LexicalAnalysis("begin a:=9; x:=2*3;b:=a+x end#"));
        analysis.Lrparser();
    }
    public SyntaxAnalysis(LexicalAnalysis lexical) {
        this.lexical = lexical;

    }

    public void scanner() {
        word = lexical.getWord();
        syn =lexical.getSyn(word);
    }

    public void Lrparser() {
        scanner();
        if (syn != 1) {
            System.out.println("'begin'错误；");
            kk = 1;
            return;
        }

        yucu();
        if (syn == 6) {
            scanner();
            if (syn == 0 && kk == 0) {
                System.out.println("success");
            } else {
                if (kk != 1)
                    System.out.println("缺‘end’错误");
                kk = 1;
            }

        }
    }

    public void yucu() {
        statement();
        while (syn==26){
            statement();
        }
        return;
    }

    public void statement() {
        scanner();
        if (syn==10){
            scanner();
            if (syn==18){
                scanner();
                expression();
            }else {
                System.out.println("赋值号错误");
                kk=1;
            }

        }else {
            System.out.println("输出语句错误");
            kk=1;
        }
    }

    public void expression() {
        term();
        while (syn==13||syn==14){
            scanner();
            term();

        }

    }

    public void term() {
        factor();
        while (syn==15||syn==16){
            scanner();
            factor();
        }
    }

    public void factor() {
        if(syn==10||syn==11){
            scanner();
        }
        else if (syn==27){
            scanner();
            expression();
            if (syn==28){
                scanner();
            }
            else{
                System.out.println("')'错误");
                kk=1;
            }
        }else {
            System.out.println("表达式错误");
            kk=1;
        }
        return;
    }
}

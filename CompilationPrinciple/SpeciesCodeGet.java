package CompilationPrinciple;

public interface SpeciesCodeGet {
    /**
     * 为了增加程序的可扩展性,因为单词正规式不同，所以把这个方法提出来叫给调用者实现
     * @param word 单词
     * @return 这个单词对应的种别码
     */
    int getCode(String word);
}

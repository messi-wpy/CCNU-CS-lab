#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <cstring>
#include <math.h>
using namespace std;
//hash链接发处理冲突，如果冲突，则用next到下一个
struct hashItem {
    string key;
    int val = 0;
    hashItem *next;
};

//网上查找的常用的字符串hash函数算法,冲突度较低
unsigned int SDBMHash(const char *str) {
    unsigned int hash = 0;

    while (*str) {
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    //转换成100以内数
    return (hash & 0x7FFFFFFF) % 100;
}

class Myhash {
private:
    hashItem *hashmap;
    int n;

    int hashFunction(const string &key) {
        return SDBMHash(key.c_str());

    }

public:
    Myhash() {
        hashmap = new hashItem[101];
        n = 0;

    }

    void add(const string &key) {
        int hashcode = hashFunction(key);
        //处理冲突
        if (hashmap[hashcode].key != key && hashmap[hashcode].val != 0) {
            hashItem *ptr = &hashmap[hashcode];

            hashItem *newItem = new hashItem;
            newItem->key = key;
            newItem->val = 1;
            newItem->next = nullptr;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = newItem;
        } else {
            hashmap[hashcode].val++;
            hashmap[hashcode].key = key;
            hashmap[hashcode].next = nullptr;

        }
    }

    int getvalue(const string &key) {
        int index = hashFunction(key);
        hashItem *ptr = &hashmap[index];
        if (ptr->key != key) {
            while (ptr->next != nullptr) {
                ptr = ptr->next;
                if (ptr->key == key)
                    return ptr->val;
            }
            return 0;
        }
        return ptr->val;

    }

    int getNum() {
        return n;
    }


};

string c_keywords[100];
void count(fstream &file,Myhash & myhash,Myhash & keymap){
    while (!file.eof()) {
        string temp;
        file >> temp;
        //统计字符+-=/....
        for (int i = 0; i <temp.length() ; ++i) {
            if (keymap.getvalue(temp.substr(i,1))!=0){
                myhash.add(temp.substr(i,1));
            }
        }
        if (keymap.getvalue(temp) != 0) {
            myhash.add(temp);
        }
    }

}
int main() {
    Myhash hash_1;
    Myhash hash_2;
    Myhash keymap;
    fstream file1;
    fstream file2;
    ifstream wordsFile;
    wordsFile.open("cppKeyWords.txt");
    //file.open("SourceCode.txt");
    int j = 0;
    while (!wordsFile.eof()) {
        string temp;
        wordsFile >> temp;
        c_keywords[j++] = temp;
        keymap.add(temp);
    }
    wordsFile.close();

    file1.open("SourceCode1.txt");
    file2.open("SourceCode2.txt");
    count(file1,hash_1,keymap);
    count(file2,hash_2,keymap);
    file1.close();
    file2.close();

    //计算相似度，用两个向量的余弦值来代替相似度
    float sum,absA,absB;
    sum=absA=absB=0;
    for (int i = 0; i < j; ++i) {
        float a,b;
        a=hash_1.getvalue(c_keywords[i]);
        b=hash_2.getvalue(c_keywords[i]);
        sum+=(a*b);
        absA+=a*a;
        absB+=b*b;

        cout << c_keywords[i] << "             sourceCode1: " << hash_1.getvalue(c_keywords[i]) <<"    sourceCode2:"<<hash_2.getvalue(c_keywords[i]) <<endl;

    }
    cout<<endl;
    float  result=sum/(sqrt(absA)*sqrt(absB));
    cout<<"hash 计算相似度："<<result<<endl;

    return 0;
}
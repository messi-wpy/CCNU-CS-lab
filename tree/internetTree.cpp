#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <string.h>
#include <fstream>
using namespace std;
vector<string> split(string str,string pattern);
typedef struct BiTNode {
    string data;
    string ip;
    string description;
    struct BiTNode* lchild,*rchild;
    bool left,right,isLeaf;
} BiTNode,*BitTree;


typedef struct {
    BitTree ptr;
    int task;
}stackElem;


string  visit( BiTNode*  const bitTree){
    cout<<bitTree->data;
    return bitTree->data;

}

//前序遍历
void PreOrder(BiTNode* tree){
    if (tree== nullptr)return;
    visit(tree);
    PreOrder(tree->lchild);
    PreOrder(tree->rchild);
}
//中序遍历stack实现
//头结点
void InOrder(BitTree tree){
    stack<stackElem>stack;
    stackElem elem;
    elem.task=0;
    elem.ptr = tree;
    if (tree)
        stack.push(elem);
    while (!stack.empty()){
        stackElem temp=stack.top();
        stack.pop();
        if (temp.task==1)
            visit(temp.ptr);
        else{
            BitTree  tree=temp.ptr;
            temp.ptr=tree->rchild;
            stack.push(temp);

            temp.ptr=tree;
            temp.task=1;
            stack.push(temp);

            temp.ptr=tree->lchild;
            temp.task=0;
            stack.push(temp);

        };

    }

}

void createTree(BitTree tree){
    char data;
    cout<<"先顺输入二叉树,#号代表空节点"<<endl;
    cin>>data;
    if (data=='#')
        tree= nullptr;
    else{
        tree=new BiTNode;
        tree->data=data;
        createTree(tree->lchild);
        createTree(tree->rchild);
    }

}

//求树深度
int BitTreeDepth(BitTree tree){
    if (tree== nullptr)
        return 0;
    int left=BitTreeDepth(tree->lchild);
    int right=BitTreeDepth(tree->rchild);
    return (left>right?left:right)+1;

}
//先序求深度
void PreDepth(BitTree tree,int h,int &depth){
    if (tree){
        if (h>depth)depth=h;
        PreDepth(tree->lchild,h+1,depth);
        PreDepth(tree->rchild,h+1,depth);

    }
}

/**
 * 孩子-兄弟链表
 * 层次输入,从上到下从左到右
 * 输入形式:(father,son)父节点#,子节点#表结束
 * (#,a)  (a,b)...(..,#)结束
 *
 * @param root 根节点
 */
void createTree(BiTNode& root){
    root.lchild=root.rchild= nullptr;
    char *fatherData= new char[20];
    char *sonData=new char [20];
    BitTree son;
    BitTree father;

    BiTNode *lastChild;

    root.data="#";
    root.isLeaf=false;
    queue<BiTNode*>queue1;
    queue1.push(&root);
    for (cin>>fatherData>>sonData;strcmp(sonData,"#");cin>>fatherData>>sonData) {
        BiTNode *node=new BiTNode;
        node->lchild=node->rchild= nullptr;
        node->data=sonData;
        cin>>node->isLeaf;
        if (node->isLeaf)
            cin>>node->ip>>node->description;


        queue1.push(node);
        BiTNode *front=queue1.front();
        while (fatherData!=front->data){
            queue1.pop();
            front=queue1.front();
        }
        if (front->lchild== nullptr){
            front->lchild=node;
            lastChild=node;
        } else{
            lastChild->rchild=node;
            lastChild=node;
        }
    }
}

/**
 * 先序遍历创建
 * @param tree
 */

void createTree2(BiTNode& tree,ifstream &file){
    tree.rchild=tree.lchild= nullptr;
    string data;
    bool left,rigth;
    file>>data>>left>>rigth;
    tree.data=data;
    bool isLeaf;
    file>>isLeaf;
    tree.isLeaf=isLeaf;
    if (isLeaf)
        file>>tree.ip>>tree.description;
    if (left) {
        tree.lchild = new BiTNode;
        createTree2(*tree.lchild,file);
    }
    if (rigth) {
        tree.rchild = new BiTNode;
        createTree2(*tree.rchild,file);
    }
}

void output(BiTNode* tree,list<string>l){
    while (tree){
        l.push_front(tree->data);
        if(tree->lchild== nullptr) {
            tree->left= false;
            list<string>::iterator it = l.begin();
            for (; it != l.end(); it++) {
                if (*it == "#")break;
                    cout << *it;
                if (*(++it)!="#"){
                    cout<<'.';
                    it--;
                }
            }
            cout<<endl;
            cout<<"ip: ";
            cout<<tree->ip<<" description: "<<tree->description<<endl<<endl;
        } else {
            tree->left= true;
            output(tree->lchild, l);
        }
        l.pop_front();
        tree->right= tree->rchild != nullptr;
        tree=tree->rchild;

    }

}

void saveData( BiTNode &tree,ofstream &file){
    file<<tree.data<<" "<<tree.left<<" "<<tree.right<<" "<<tree.isLeaf;
    if (tree.isLeaf)
        file<<" "<<tree.ip<<" "<<tree.description;
    file<<endl;

    if (tree.left)
        saveData(*tree.lchild,file);
    if(tree.right)
        saveData(*tree.rchild,file);

}

vector<string> split(string str,string pattern)
{
     string::size_type pos;
     vector<string> result;
     str+=pattern;//扩展字符串以方便操作
     int size=str.size();

     for(int i=0; i<size; i++)
     {
         pos=str.find(pattern,i);
         if(pos<size)
         {
             std::string s=str.substr(i,pos-i);
             result.push_back(s);
             i=pos+pattern.size()-1;
         }
     }
     return result;
 }
void find(vector<string>&v, BiTNode *tree, bool &isFind,int i,BitTree& prt){
    if (v[i]==tree->data)
        i--;
    else{
        i=v.size()-1;
    }
    if (i<0){

        isFind= true;
        prt=tree;
        cout<<tree->ip<<"  "<<tree->description<<endl;
        return;
    }
    if (tree->left)
        find(v,tree->lchild,isFind,i,prt);
    else if (tree->right)
        find(v,tree->rchild,isFind,i,prt);

}
void find2(vector<string>&v, BiTNode *tree, bool &isFind,int i,BitTree& prt){
    if (v[i]==tree->data)
        i++;
    else{
        i=0;
    }
    if (i==v.size()-1){

        isFind= true;
        prt=tree;
        cout<<tree->ip<<"  "<<tree->description<<endl;
        return;
    }
    if (tree->left)
        find2(v,tree->lchild,isFind,i,prt);
    else if (tree->right)
        find2(v,tree->rchild,isFind,i,prt);

}
void findIP( BiTNode* tree){
    cout<<"要查找的域名:  "<<endl;
    string name;
    cin>>name;
    vector<string>result=split(name,".");
    bool isfind= false;
    BitTree prt;
    find(result,tree,isfind,result.size()-1,prt);
    if (!isfind)
        cout<<"not find"<<endl;



}
void deleteIt(BiTNode*tree){
    BitTree prt=tree;
    prt=tree->lchild;
    tree->lchild=tree->lchild->lchild;
    BitTree temp=tree->lchild;
    if (temp== nullptr)
        tree->lchild=prt->rchild;
    else
        while (temp->rchild!= nullptr)
            temp=temp->rchild;
    temp->rchild=prt->rchild;
    delete(prt);
    cout<<"delete successfully"<<endl;


}
void deleteNode(BiTNode *tree){
    cout<<"要删除的域名(反着):(输入完整的，最后一个代表要删除的节点)  "<<endl;
    string name;
    cin>>name;
    vector<string>result=split(name,".");
    bool isfind= false;
    BitTree prt;
    find2(result,tree,isfind,0,prt);
    if (!isfind)
        cout<<"not find"<<endl;
    else
        deleteIt(prt);



}
void insert(BiTNode*tree){
    cout<<"要插入的节点(反着输入完整，最后一个节点代表要插入的)"<<endl;
    string name;
    cin>>name;
    vector<string>result=split(name,".");
    BiTNode *newNode=new BiTNode;
    newNode->data=result[result.size()-1];
    newNode->lchild=newNode->rchild= nullptr;
    newNode->left=newNode->right=newNode->left= false;
    bool isfind= false;
    BitTree prt;
    find2(result,tree,isfind,0,prt);
    if (!isfind)
        cout<<"not find"<<endl;
    else
    {
        BitTree temp=prt->lchild;
        if (!temp) {
            prt->lchild = newNode;
            prt->left= true;
            newNode->isLeaf= true;
            newNode->ip=prt->ip;
            newNode->description=prt->description;
        } else{
            newNode->lchild=prt->lchild;
            newNode->left=true;
            prt->lchild=newNode;

        }
    }
}

int main() {
    BiTNode tree;
    list<string>list1;
    //读
    ifstream infile;
    //写
    ofstream outfile;
    string s;
    infile.open("TreeData.dat",ios::in);
    if (!infile){
        printf("文件不存在，需要输入格式(#,a,1/0 --> ip  description)  (a,b)...(..,#)结束\n");
        createTree(tree);
    } else{
        createTree2(tree,infile);
        infile.close();
    }
    output(&tree,list1);
    cout<<"查找-->find\n删除-->delete\n插入-->insert\n退出-->quit\n";
    string choose;
    cin>>choose;
    while (choose!="quit"){
        if(choose=="find")
            findIP(&tree);
        else if (choose=="delete") {
            deleteNode(&tree);
            output(&tree,list1);
        }
        else if(choose=="insert"){
            insert(&tree);
            output(&tree,list1);

        }
        cout<<"查找-->find\n删除-->delete\n插入-->insert\n退出-->quit\n";
        cin>>choose;

    }





    outfile.open("TreeData.dat",ios::out);
    saveData(tree,outfile);
    outfile.close();








    return 0;
}



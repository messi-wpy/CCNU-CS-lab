#include <iostream>
#include <stack>
using namespace std;
typedef struct BiTNode {
    char data;
    struct BiTNode* lchild,*rchild;
} BiTNode,*BitTree;
typedef struct {
    BitTree ptr;
    int task;

}stackElem;
int  visit( BiTNode*  const bitTree){
    printf("%d  ",bitTree->data);
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


int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}



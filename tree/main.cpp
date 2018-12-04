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
int main() {


    cout << "Hello, World!" << std::endl;
    return 0;
}



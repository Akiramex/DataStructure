/**
 * @file ThreadBT.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;
#define ElemType char


//线索二叉树节点声明
typedef struct node
{
    ElemType data;
    int ltag,rtag;  //增加的线索标记
    struct node *lchild;
    struct node *rchild;
}TBTNode;

//为了使线索二叉树的创建算法设计方便，添加一个头结点root

TBTNode *pre;
void Thread(TBTNode *& p)   //线索化，类似于中序递归遍历
{
    if(p != NULL)
    {
        Thread(p->lchild);  //左孩子线索化

        //左孩子不存在，进行线索化
        if(p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        else
            p->ltag = 0;

        //右孩子不存在，进行线索化
        if(pre->rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        else
            pre->rtag = 0;
        pre = p;

        Thread(p->rchild); //右孩子线索化
    }
}

TBTNode *CreateThread(TBTNode *b)
{
    TBTNode *root;
    root = (TBTNode *)malloc(sizeof(TBTNode));
    root->ltag = 0; root->rtag =1;
    root->lchild = b;
    if(b == NULL)   //空二叉树
        root->lchild = root;
    else
    {
        root->lchild = b;
        pre = root; //pre 是节点 p的前驱节点
        Thread(b);  //中序遍历线索化二叉树
        //递归结束后，pre指向最后一个节点
        pre->rchild = root;
        pre->rtag = 1;
        root->rchild = pre;
    }
    return root;
}

//遍历中序线索二叉树
void ThInOrder(TBTNode *tb)
{
    TBTNode *p = tb->lchild;    // p指向首节点
    while(p != tb)
    {
        while(p->ltag == 0) p = p->lchild;  //找到开始节点
        printf("%c",p->data);   //访问开始节点
        while(p->rtag == 1 && p->rchild != tb)  // p没有右孩子
        {
            p = p->rchild;
            printf("%c",p->data);
        } 
        p = p->rchild;  //访问 p的右孩子，或者后继节点，由 p->rtag决定
    }
}

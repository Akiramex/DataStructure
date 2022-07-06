/**
 * @file btree.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#define ElemType char
#define MaxSize 50

/*--------------------------------------二叉链的双链表的定义---------------------------------------*/
typedef struct node {
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}BTnode;

/*----------------------------------------双链表基本运算的实现------------------------------------*/
//创建二叉树
void CreateBTree(BTnode *&b, char * str)
{
    BTnode *St[MaxSize], *p;    //St数组作为循序栈
    int top = -1, k, j = 0;     //top作为栈顶指针
    char ch;
    b = NULL;                   //初始时二叉链为空
    ch = str[j];
    while (ch != '\0')          //循环扫描str的每个字符
    {
        switch (ch)
        {
        case '(': top++; St[top] = p; k = 1; break; //开始处理左孩子节点
        case ')': top--; break; //栈顶节点的子树处理完毕
        case ',': k = 2; break; //开始处理右孩子节点
        default:                
            p = (BTnode*)malloc(sizeof(BTnode));
            p->data = ch;
            p->lchild = p->rchild = NULL;   //左右指针都设为空
            if(b == NULL)   //若尚未建立树根节点
            {
                b = p;      //p所指的节点作为根节点
            }
            else            //已建立树根节点
            {
                switch(k)
                { 
                    case 1:St[top]->lchild = p; break;
                    case 2:St[top]->rchild = p; break;
                }
            }
            break;
        }
        j++;        //继续扫描
        ch = str[j];
    }
}

//销毁二叉树
void DestroyBTree(BTnode *&b)   //后序遍历
{
    if(b != NULL)
    {
        DestroyBTree(b->lchild);
        DestroyBTree(b->rchild);
        free(b);
    }
}

//查找节点*
BTnode* FindNode(BTnode *b, ElemType x)
{
    BTnode *p;
    if(b == NULL)
        return NULL;
    else if(b->data == x)
        return b;
    else
    {
        p = FindNode(b->lchild, x);
        if(p != NULL)
            return p;
        else
            return FindNode(b->rchild, x);
    }
}

//找孩子节点
BTnode * LchildNode(BTnode * p)
{
    return p->lchild;
}
BTnode * rchildNode(BTnode * p)
{
    return p->rchild;
}

//求二叉树高度
int BTHeight(BTnode *b)
{
    int lchildh, rchildh;
    if(b == NULL)
        return 0;
    else
    {
        lchildh = BTHeight(b->lchild);
        rchildh = BTHeight(b->rchild);
        return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
    }
}

//输出二叉树
void DispBTree(BTnode* b)
{
    if(b != NULL)
    {
        printf("%c",b->data);
        if(b->lchild != NULL || b->rchild != NULL)
        {
            printf("(");
            DispBTree(b->lchild);
            if(b->rchild != NULL)
                printf(",");
            DispBTree(b->rchild);
            printf(")");
        }
    }
}

/*----------------------------------------双链表的函数------------------------------------*/
//遍历算法
void PreOrder(BTnode *b)    //先序遍历
{
    if(b != NULL)
    {
        printf("%c",b->data);
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}

void PreOrder(BTnode *b)    //中序遍历
{
    if(b != NULL)
    {
        PreOrder(b->lchild);
        printf("%c",b->data);
        PreOrder(b->rchild);
    }
}

void PreOrder(BTnode *b)    //后序遍历
{
    if(b != NULL)
    {
        PreOrder(b->lchild);
        PreOrder(b->rchild);
        printf("%c",b->data);
    }
}

//计算二叉树的所有节点个数
int Nodes(BTnode *b)
{
    if(b == NULL)
        return 0;
    else
        return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

//输出二叉树的叶子节点
void DispLeaf(BTnode *b)
{
    if(b != NULL)
    {
        if(b->lchild == NULL && b->rchild == NULL)
            printf("%c", b->data);
        else
        {
            DispLeaf(b->lchild);
            DispLeaf(b->rchild);
        }
    }
}

//求二叉树 b中的第 K层的节点个数
void Lnodenum(BTnode *b, int h, int k, int &n)
{
    if(b == NULL)
        return;
    else
    {
        if(h == k) n++;
        else if(h < k)
        {
            Lnodenum(b->lchild, h+1, k, n);
            Lnodenum(b->rchild, h+1, k, n);
        }
    }
} 

//判断两个二叉树是否相似
bool Like(BTnode* b1, BTnode* b2)
{
    bool like1,like2;
    if(b1 == NULL && b2== NULL)
        return true;
    else if(b1 == NULL || b2 == NULL)   //一个为空，另一不为空
        return false;
    else
    {
        like1 = Like(b1->lchild, b2->lchild);
        like2 = Like(b1->rchild, b2->rchild);
        return(like1 && like2);
    }
}

//输出值为 x的节点的所有祖先节点
bool ancestor(BTnode *b, ElemType x)
{
    if(b == NULL)
        return false;
    else if (b->lchild != NULL && b->lchild->data == x || b->rchild != NULL && b->rchild->data == x)
    {
        printf("%c ", b->data);
        return true;
    }
    else if (ancestor(b->lchild, x) || ancestor(b->rchild, x))
    {
        printf("%c ", b->data);
        return true;
    }
    else return false;
}
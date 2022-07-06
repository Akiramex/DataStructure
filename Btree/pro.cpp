/**
 * @file pro.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50


typedef struct node {
    char data;
    struct node *lchild;
    struct node *rchild;
}BTnode;
#define ElemType BTnode
typedef struct{
    ElemType *data[MaxSize];
    int top;    //栈顶指针
}SqStack;


void InitStack(SqStack* &s)
{
    s = (SqStack*)malloc(sizeof(SqStack));
    s->top = -1;
}
void DestoryStack(SqStack* &s)
{
    free(s);
}
bool StackEmpty(SqStack *s)
{
    return(s->top == -1);
}
bool Push(SqStack* &s, ElemType* e)
{
    if(s->top == MaxSize - 1) return false; //栈满的情况
    s->top++;   //栈顶指针增 1
    s->data[s->top] = e;
    return true;
}
bool Pop(SqStack* &s, ElemType* &e)
{
    if(s->top == -1) return false;  //栈空的情况
    e = s->data[s->top];    //保存出栈元素
    s->top--;   //栈顶指针减 1
    return true;
}
bool GetTop(SqStack* s, ElemType *&e)
{
    if(s->top == -1) return false;  //栈空的情况
    e = s->data[s->top];
    return true;
}

//先序遍历的 非递归算法 1
//由于栈的特性是 先进后出，要实现先序遍历就得 先让右孩子进栈，再让左孩子进栈
void PreOrder1(BTnode *b)
{
    BTnode *p;
    SqStack *st;
    InitStack(st);
    if(b != NULL)
    {
        Push(st, b);
        while(!StackEmpty(st))
        {
            Pop(st, p);
            printf("%c", p->data);
            if(p->rchild != NULL)
                Push(st, p->rchild);
            if(p->lchild != NULL)
                Push(st, p->lchild);
        }
        printf("\n");
    }
    DestoryStack(st);
}

//先序遍历的 非递归算法 2
void PreOrder2(BTnode* b)
{
    BTnode *p;
    SqStack *st;
    InitStack(st);
    p = b;
    while(!StackEmpty(st) || p != NULL)
    {
        //访问p及其所有左下节点并进栈，至 p为空
        while(p != NULL)
        {
            printf("%c", p->data);
            Push(st, p);
            p = p->lchild; 
        }
        //此时栈顶节点没有左孩子，或者左子树已经遍历
        if(!StackEmpty(st))
        {
            Pop(st, p);
            p = p->rchild;  //转而处理右子树
        }
    }
    printf("\n");
    DestoryStack(st);
}

//中序遍历 的非递归算法
void InOrder1(BTnode *b)
{
    BTnode *p;
    SqStack *st;
    p = b;
    while (!StackEmpty(st) || p != NULL)
    {
        while(p != NULL)
        {
            Push(st, p);
            p = p->lchild;
        }
        //此时栈顶节点没有左孩子或者左子树已遍历过
        if(!StackEmpty(st))
        {
            Pop(st, p);
            printf("%c",p->data);
            p = p->rchild;  //转而处理右子树
        }
    }
    printf("\n");
    DestoryStack(st);
}

//后序遍历 的非递归算法
//后序遍历非递归算法有这样的特点：当访问某个节点时，栈中保存的正好是该节点的所有祖先节点，栈顶到栈底正好是该节点双亲节点到根节点的逆序
void PostOrder1(BTnode *b)
{
    BTnode *p, *r;
    bool flag;
    SqStack *st;
    InitStack(st);
    p = b;
    do
    {
        while(p != NULL)
        {
            Push(st,p);
            p = p->lchild;
        }
        r = NULL;   //r指向刚访问的节点，初始时为空
        flag = true;//flag为真，表示正在处理栈顶节点
        while(!StackEmpty(st) && flag)
        {
            GetTop(st,p);   //取出当前栈顶节点 p
            if (p->rchild == r) //表示 p右孩子为空或者 为刚刚访问过的节点
            {
                printf("%c",p->data);   //访问 p节点
                Pop(st,p);
                r = p;  //r指向刚访问过的节点
            }
            else
            {
                p = p->rchild;  //转而处理右子树
                flag = false;
            }
        }
    } while (!StackEmpty(st));
    printf("\n");
    DestoryStack(st);
}

//利用后序非递归算法，输出根节点到每个叶子节点的逆序列路径
void AllPath1(BTnode *b)
{
    BTnode *p, *r;
    SqStack* st;
    bool flag;
    p = b;
    do
    {
        while (p != NULL)
        {
            Push(st,p);
            p = p->lchild;
        }
        r = NULL;
        flag = true;
        while (!StackEmpty(st) && flag)
        {
            GetTop(st,p);
            if(p ->rchild == r)
            {
                if (p->lchild == NULL && p->rchild == NULL) //若 p为叶子节点
                {
                    for (int i = st->top; i > 0; i--)   //输出序列
                    {
                        printf("%c->",st->data[i]->data);
                    }
                    printf("%c\n",st->data[0]->data); 
                }
                Pop(st,p);
                r = p;
            }
            else
            {
                p = p->rchild;
                flag = false;
            }
        }
    } while (!StackEmpty(st));
    printf("\n");
    DestoryStack(st);
}
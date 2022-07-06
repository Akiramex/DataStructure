/**
 * @file pro2.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define MaxSize 50
#include<iostream>
using namespace std;

typedef struct node{
    char data;
    struct node *lchild;
    struct node *rchild;
}BTNode;
typedef struct{
    BTNode *data[MaxSize];
    int front, rear;
}SqQueue;

void InitQueue(SqQueue*& q)
{
    q = (SqQueue*)malloc(sizeof(SqQueue));
    q->front = q->front = 0;
}

void DestroyQueue(SqQueue *&q)
{
    free(q);
}

bool QueueEmpty(SqQueue* q)
{
    return(q->front == q->rear);
}

bool enQueue(SqQueue *&q, BTNode *e)
{
    if((q->rear + 1) % MaxSize == q->front)
        return false;
    q->rear = (q->rear + 1) % MaxSize;
    q->data[q->rear] = e;
    return true;
}

bool deQueue(SqQueue *&q, BTNode *&e)
{
    if(q->rear == q->front)
        return false;
    q->front = (q->front + 1) % MaxSize;
    e = q->data[q->front];
    return true;
}

//二叉树的层次遍历算法
void LevelOrder(BTNode *b)
{
    BTNode *p;
    SqQueue *qu;
    InitQueue(qu);
    enQueue(qu,b);
    while(!QueueEmpty(qu))
    {
        deQueue(qu,p);
        printf("%c",p->data);
        if(p->lchild != NULL)
            enQueue(qu,p->lchild);
        if(p->rchild != NULL)
            enQueue(qu,p->rchild);
    }
    DestroyQueue(qu);
}

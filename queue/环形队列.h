/**
 * @file 环形队列.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#define MaxSize 50  //顺序队最大长度
#define ElemType int    //自定数据类型 默认为int

/*-------------------------------------顺序队的定义---------------------------------------*/
typedef struct
{
    ElemType data[MaxSize];
    int front,rear; //队头和队尾指针
}SqQueue;

/*---------------------------------环形队基本运算的实现------------------------------------*/
//初始化将rear front置 0
//对头指针 front 循环增 1：front = (front + 1) % MaxSize
//队尾指针 rear 循环增 1：rear = (rear + 1) % MaxSize
//队空条件：rear == front
//队满条件：队尾指针循环增 1时等于对头指针（也就是说进栈时队尾尝试进队一次，若达到队头，就认为队满了，不能进队）
//队满条件：(rear + 1) % MaxSize == front
//队内最多 MaxSize-1个元素

//初始化队列
void InitQueue (SqQueue* &q)
{
    q = (SqQueue*)malloc(sizeof(SqQueue));
    q->front = q->rear = 0;
}

//销毁队列
void DestroyQueu(SqQueue *&q)
{
    free(q);
}

//队列是否为空
bool QueueEmpty(SqQueue *q)
{
    return(q->front == q->rear);
}

//进队列
bool enQueue(SqQueue *&q, ElemType e)
{
    if((q->rear + 1) % MaxSize == q->front) //队满上溢出
        return false;   
    q->rear = (q->rear + 1) % MaxSize;
    q->data[q->rear] = e;
    return true;
}

//出队列
bool deQueue(SqQueue *&q, ElemType &e)
{
    if(q->front == q->rear) //队空下溢出
        return false;
    q->front = (q->front + 1) % MaxSize;
    e = q->data[q->front];
    return false;
}

//对于环线队列，来说如果直到队头指针和队列中的元素个数，则可以计算出队尾指针。设计一个这种环线队列
//队尾rear：(front + count) % MaxSize;
//队内最多 MaxSize个元素
typedef struct {
    ElemType data[MaxSize];
    int front;
    int count;
}QuType;

void InitQueue(QuType*&qu)
{
    qu = (QuType*)malloc(sizeof(QuType));
    qu->front = 0;
    qu->count = 0;
}

bool QueueEmpty(QuType*qu)
{
    return(qu->count == 0);
}

bool enQueue(QuType *&qu, ElemType e)
{
    int rear;
    if(qu->count = MaxSize) //队满上溢出
        return false;
    else {
        rear = (qu->front + qu->count) % MaxSize;   //队尾
        rear = (rear + 1) % MaxSize;    //队尾增 1
        qu->data[rear] = e;
        qu->count++;
        return true;
    }
}

bool deQueue(QuType*&qu, ElemType &e)
{
    if(qu->count == 0)  //队空下溢出
        return false;
    else {
        qu->front = (qu->front + 1) % MaxSize;
        e = qu->data[qu->front];
        qu->count--;
        return true;
    }
}
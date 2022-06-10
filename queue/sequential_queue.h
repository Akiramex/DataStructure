/**
 * @file sequential_queue.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    sequential queue 循序队
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

/*---------------------------------顺序队基本运算的实现------------------------------------*/
//初始化将rear front置 -1
//队空条件：rear == front
//队满条件：rear == MaxSize
//初始化队列
void InitQueue(SqQueue *&q)
{
    q = (SqQueue*)malloc(sizeof(SqQueue));
    q->front = q->rear = -1;
}

//销毁队列
void DestroyQueu(SqQueue *&q)
{
    free(q);
}

//队列是否为空
bool QueueEmpty(SqQueue *q)
{
    return(q->rear == q->front);
}

//进队列
bool enQueue(SqQueue *&q ,ElemType e)
{
    if(q->rear == MaxSize - 1)  return false;   //队满上溢出
    q->rear++;  //队尾增 1
    q->data[q->rear] = e;
    return true;
}

//出队列
bool deQueue(SqQueue *&q, ElemType &e)
{
    if(q->rear == q->front) return false;   //队空下溢出
    q->front++; //队头增 1
    e = q->data[q->front];
    return true;
}

/*---------------------------------------实际例题-----------------------------------------*/

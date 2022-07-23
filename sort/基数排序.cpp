/**
 * @file 基数排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
#define MAXD 5
#define MAXR 10 //基数
using namespace std;

typedef struct node
{
    char data[MAXD];    //MAXD为最大的关键字位数
    struct node *next;  //指向下一个节点
}NodeType;              //基数排序的数据的节点类型
//假设待排序的数据序列存放在以 p为首节点指针的单链表中
void RadixSort(NodeType *&p, int r,int d)
//d：最大关键字的位数  r：基数
{
    NodeType *head[MAXR], *tail[MAXR], *t;
    int i, j, k;
    for (i = 0; i <= d - 1; i++)        //从低位到高位循环
    {
        for (j = 0; i < r; j++)         //初始化各链对的首尾指针
            head[j] = tail[j] = NULL;   
        while(p != NULL)                //分配
        {
            k = p->data[i] - '0';
            if(head == NULL)
            {
                head[k] = p;
                tail[k] = p;
            }
            else
            {
                tail[k]->next = p;
                tail[k] = p;
            }
            p = p->next;
        }
        p = NULL;       //重新用 p来收集元素
        for (j = 0; j < r; j++)     //收集：对于每一个链队循环
        {
            if(head[j] != NULL)     //若第 j个链队是第一个非空链队
            {
                p = head[j];
                t = tail[j];
            }
            else
            {
                t->next = head[j];
                t = tail[j];
            }
        }
        t->next = NULL;     //最后一个节点 next域置空
    }
    
}
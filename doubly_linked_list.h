/**
 * @file doubly_linked_list.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    doubly linked list 双链表
*/

#include <stdlib.h>
#include <stdio.h>
#define ElemType int    //自定数据类型

/*-------------------------------------双链表的定义---------------------------------------*/

typedef struct DNode
{
    ElemType data;
    struct DNode *prior;
    struct DNode *next;
}DLinkNode;

/*--------------------------------------创建双链表----------------------------------------*/
//头插法
void CreateListF(DLinkNode *&L, ElemType a[], int n)
{
    DLinkNode *s;
    L = (DLinkNode*)malloc(sizeof(DLinkNode));  //创建头节点
    L->prior = L->next = NULL;  //前后指针域置为空
    for (int i = 0; i < n; i++) //循环建立节点
    {
        s = (DLinkNode*)malloc(sizeof(DLinkNode)); 
        s->data = a[i];
        s->next = L->next;  //将 s节点插入到头节点之后
        if(L->next != NULL) //若 L存在数据节点，修改 L->next的前驱节点
            L->next->prior = s;
        L->next = s;
        s->prior =L;
    }
}

//尾插法
void CreateListR(DLinkNode *&L, ElemType a[], int n)
{
    DLinkNode *s, *r;
    L = (DLinkNode*)malloc(sizeof(DLinkNode));  //创建头节点
    L->prior = L->next = NULL;
    r = L;  // r始终指向尾节点
    for (int i = 0; i < n; i++) //循环建立节点
    {
        s = (DLinkNode*)malloc(sizeof(DLinkNode)); 
        s->data = a[i];
        r->next = s;    // s节点插入到 r节点之后
        s->prior = r;   
        r = s;  // r指向尾节点
    }
    r->next = NULL;
}

/*---------------------------------双链表基本运算的实现------------------------------------*/
//在双链表中，有些运算算法和单链表算法是相同的，不多讨论。但是插入和删除是不同的。

//插入
bool ListInsert(DLinkNode* &L, int i, ElemType e)
{
    int j = 0;
    DLinkNode *p = L, *s;   //p指向头指针，j设为 0
    if(j < 0) return false;
    while (j < i-1 && p != NULL)    //找到第 i-1个节点
    {
        j++;
        p = p->next;
    }
    if(p == NULL)   //未找到 i-1个节点
        return false;
    else
    {
        s = (DLinkNode*)malloc(sizeof(DLinkNode));
        s->data = e;
        s->next = p->next;  //在 p节点之后插入 s节点
        if(p->next != NULL) //若 p节点存在后继节点，修改其前驱节点
            p->next->prior = s;
        s->prior = p;
        p->next = s;
        return true;
    }
}

//删除
bool ListDelete(DLinkNode* &L, int i, ElemType &e)
{
    int j = 0;    
    DLinkNode *p = L, *q;   //p指向头指针，j设为 0
    if(j < 0) return false;
    while (j < i-1 && p != NULL)    //找到第 i-1个节点
    {
        j++;
        p = p->next;
    }
    if(p == NULL)   //未找到 i-1个节点
        return false;
    else
    {
        q = p->next;
        if(q == NULL)
            return false;   //当 i节点不存在时返回 false
        e = q->data;
        p->next = q->next;  //从双链表中删除节点 q
        if(q->next != NULL) //存在后继节点
            q->next->prior = p;
        free(q);
        return true;
    }
}

/*---------------------------------------实际例题-----------------------------------------*/
//设计一个算法，将一个带头结点双链表逆序
void reverse(DLinkNode *&L)
{
    DLinkNode *p = L->next, *q; //p指向首节点
    L->next = NULL; //构建只有头节点的链表
    while(p != NULL)    //扫描 L的所有节点
    {
        q = p->next;    // q保存 p的后继节点
        p->next = L->next;  //采用头插法插入节点
        if(L->next != NULL) //若 L中存在数据元素
            L->next->prior = p;
        p->prior = L;
        L->next = p;
        p = q;
    }
}

//有一个带头结点的双链表 L(至少有一个数据节点)，设计一个算法使其元素递增有序排列
void sort(DLinkNode* &L)
{
    DLinkNode *p = L->next->next, *pre, *q;
    L->next->next = NULL;   //构造一个只有首节点的双链表
    while (p != NULL)
    {
        q = p->next;    //q保存 p的后继节点
        pre = L;
        while(pre->next != NULL && pre->next->data < p->data)   //循环找到插入节点的前驱节点 pre
            pre = pre->next;
        p->next = pre->next;    //在 pre后插入 p节点
        if(pre->next != NULL)
            pre->next->prior = p;
        pre->next = p;
        p->prior = pre;
        p = q;  //扫描剩余节点
    }
}
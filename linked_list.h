/**
 * @file linked_list.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    linked_list 单链表

    基础知识：
    头节点 head：通常每个链表都会包含一个头节点，并通过头节点的指针（头指针 head pointer）唯一标识该链表
    首指针 first pointer：指向首节点或者开始节点的指针
    尾指针 tail pointer：指向尾节点的指针
*/

#include <stdlib.h>
#include <stdio.h>
#define ElemType int    //自定数据类型

/*-------------------------------------单链表的定义---------------------------------------*/

typedef struct LNode {
    ElemType data;  //数据域
    struct LNode* next; //存放后继节点
}LinkNode;


/*--------------------------------------创建单链表---------------------------------------*/
//头插法    使用头插法建表时链表的元素顺序与 a顺序相反
void CreateListF(LinkNode* &L, ElemType a[], int n)
{
    LinkNode* s;
    L = (LinkNode*)malloc(sizeof(LinkNode));    //开辟到堆区
    L->next = NULL; //创建头节点，next域置为空
    for (int i = 0; i < n; i++) //循环创建节点 s
    {
        s = (LinkNode*)malloc(sizeof(LinkNode));
        s->data =a[i];
        s->next = L->next;
        L->next = s;
    }
}

//尾插法 链表与 a数组元素顺序相同
void CreateListR(LinkNode* &L, ElemType a[], int n)
{
    LinkNode* s,* r;    
    L = (LinkNode*)malloc(sizeof(LinkNode));
    r = L;  //r指向尾节点,初始时指向头节点
    for (int i = 0; i < n; i++)
    {
        s=(LinkNode*)malloc(sizeof(LinkNode));
        s->data = a[i];
        r->next = s;    //将 s节点插入到 r节点前
        r = s;
    }
    r->next = NULL; //尾节点 next域置为空
}


/*---------------------------------单链表基本运算的实现------------------------------------*/
//初始化单链表
void InitList(LinkNode* &L)
{
    L = (LinkNode*)malloc(sizeof(LinkNode));
    L->next = NULL;
}

//销毁单链表
void DestroyList(LinkNode* &L)
{
    LinkNode *pre, *p;
    pre = L, p = L->next;   //pre指向头节点，p指向首节点
    while(p != NULL)
    {
        free(pre);
        pre = p;    //同步后移
        p = pre->next;
    }
    free(pre);
}

//判断单链表是否为空表
bool ListEmpty(LinkNode* L)
{
    return(L->next == NULL);
}

//求单链表的长度
int LinkLength(LinkNode* L)
{
    int n = 0;
    LinkNode* p = L;    //p指向头节点
    while(p->next != NULL)  //循环至尾节点
    {
        p=p->next;
        n++;
    }
    return n;
}
 
 //输出单链表
 void DispLink(LinkNode* L)
 {
     LinkNode *p = L->next; //p指向首节点
     while(p != NULL)
     {
         printf("%d ",p->data);
         p=p->next;
     }
     printf("\n");
 }

 //求链表中的某个数据元素值
 bool GetElem(LinkNode* L, int i, ElemType &e)
 {
     int j = 0; //j用于记录链表长度
     LinkNode *p = L;
     if(i <= 0) return false;   //合法性检查
     while (p != NULL && j < i) //循环检索，直至 p到尾节点或者 j=i
     {
         j++;
         p = p->next;
     }
     if(p == NULL) return false;
     else   //j=i
     {
         e = p->data;
         return true;
     }
 }

 //按元素值查找
 int LocateElem(LinkNode* L, ElemType e)
 {
     int i = 1;
     LinkNode *p = L->next; //指向首节点
     while(p != NULL && p->data != e)   //循环检索，直到链表尾 或者 找到元素
     {
         p = p->next;
         i++;
     }
     if(p == NULL) return(0);   //不存在值为 e的节点，返回0
     else return(i);    //存在值为 e的节点，返回逻辑序号 i3e
 }

 //插入数据元素
 bool ListInsert(LinkNode* &L, int i, ElemType e)
 {
     int j = 0;
     LinkNode *p = L, *s;
     if(i <= 0) return false;   //合法性检查
     while(p != NULL && j < i-1)  //循环检索，直至 p到尾节点或者 j=i-1
     {
         j++;
         p=p->next;
     }
    if(p == NULL) return false;//未找到第 i-1个数据节点
    else
    {
        s = (LinkNode*)malloc(sizeof(LinkNode));
        s->data = e;
        s ->next = p->next; //将节点 s插入到节点 p之后
        p->next = s;
        return true;
    }
}

//删除数据元素
bool ListDelete(LinkNode* &L, int i, ElemType &e)
{
    int j = 0;
    LinkNode *p = L, *q;
    if(i <= 0) return false;   //合法性检查
    while (p != NULL && j < i-1)//循环检索，直至 p到尾节点或者 j=i-1
    {
        j++;
        p = p->next;
    }
    if (p = NULL) return false; //未找到第 i-1个数据节点
    else
    {
        q = p->next;    //q指向第 i给节点
        if(q = NULL) return false;  //q节点不存在
        e = q->data;
        p->next = q->next;
        free(q);
        return true;
    }
}


/**
 * @file hashTable拉链法.cpp
 * @author Akirq
 * @brief 
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;

typedef int KeyType;
typedef struct node
{
    KeyType key;    //关键字域
    struct node *next;  //下一个节点指针
}NodeType;
typedef struct
{
    NodeType *firstp;   //首节点指针
}HashTable;             //哈希表单元类型

//1、插入
void InsertHT(HashTable ha[], int &n, int p, KeyType k)
{
    int adr;
    adr = k % p;
    NodeType *q;
    q = (NodeType*)malloc(sizeof(NodeType));
    q->key = k;
    q->next = NULL;
    if (ha[adr].firstp == NULL)     //首节点为空
        ha[adr].firstp = q;
    else                            //首节点不为空
    {
        q->next = ha[adr].firstp;   //头插法
        ha[adr].firstp = q;
    }
    n++;
}

//2、建表
void CreateHT(HashTable ha[], int &n, int m, int p, KeyType keys[], int n1)
//由关键字序列 keys[](n1个元素)创建哈希表
{
    for (int i = 0; i < m; i++)
        ha[i].firstp = NULL;
    n = 0;
    for (int i = 0; i < n1; i++)
        InsertHT(ha,n,p,keys[i]);
}

//3、删除
bool DeleteHT(HashTable ha[], int &n, int m, int p, KeyType k)
{
    int adr;
    adr = k % p;
    NodeType *q, *preq;
    q = ha[adr].firstp;
    if (q != NULL)
        return false;
    if (q->key == k)
    {
        ha[adr].firstp = q->next;
        free(q);
        n--;
        return true;
    }
    
    //首节点不为 k
    preq = q; q = q->next;
    while (q != NULL && q->key != k)
    {
        preq = q;
        q = q->next;
    }
    if (q != NULL)                   //找到节点
    {
        preq->next = q->next;
        free(q);
        n--;
        return true;
    }
    else return false;              //未找到节点
}

//4、查找
void SearchHT(HashTable ha[], int p, KeyType k)
{
    int i = 1, adr;
    adr = k % p;
    NodeType *q;
    q = ha[adr].firstp;
    while (q != NULL && q->key != k)
    {
        i++;
        q = q->next;
    }
    if (q != NULL)
        printf("成功：关键字%d，比较%d次\n,k,i");
    else
        printf("失败：关键字%d，比较%d次\n,k,i");
}

//5、ASL平均查找长度
void ASL(HashTable ha[], int n, int m)
{
    int succ = 0, unsucc = 0, s;
    NodeType *q;
    for (int i = 0; i < m; i++)     //扫描所有哈希表地址空间
    { 
        s = 0;
        q = ha[i].firstp;
        while (q != NULL)           //扫描单链表 i的所有节点
        {
            q = q->next;
            s++;                // s记录当前节点是对应单链表的第几节点
            succ = succ + s;
        }
        unsucc = unsucc + s;
    }
    printf("成功情况下ASL(%d)=%g\n,n,succ*1.0/n");
    printf("不成功情况下ASL(%d)=%g\n,n,unsucc*1.0/m");
}
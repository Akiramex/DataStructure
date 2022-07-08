/**
 * @file HuffmanTree.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define N 20
#include<iostream>
using namespace std;

typedef struct 
{
    char data;
    double weight;
    int parent;
    int lchild;
    int rchild;
}HTNode;

void CreateHT(HTNode ht[], int n0)
{
    int i, k, lnode, rnode;
    double min1, min2;
    for (i = 0; i < 2 * n0 - 1; i++)
        ht[i].lchild = ht[i].rchild = ht[i].parent = -1;    //所有节点的相关域初值 -1

    for (i = n0; i < 2 * n0 - 2; i++)   //处理 n0 -1个分支节点
    {
        min1 = min2 = 32767;
        lnode = rnode = -1;
        for (k = 0; k <= i - 1; k++)    //查找权值最低的两个节点
        {
            if(ht[k].parent == -1)      //在尚未构造二叉树的节点中查找
            {
                if(ht[k].weight < min1)     //min1比min2更小
                {
                    min2 = min1;        //找到更小的值就把当前的值赋给 min2
                    rnode = lnode;

                    min1 = ht[k].weight;
                    lnode = k;
                }
                else if(ht[k].weight < min2)
                {
                    min2 = ht[k].weight;
                    rnode = k;
                }
            }
            ht[i].weight = ht[lnode].weight + ht[rnode].weight; //ht[i]作为双亲节点
            ht[i].lchild = lnode; ht[i].rchild = rnode; 
            ht[lnode].parent = i; ht[rnode].parent = i;
        }
    }
}

//哈夫曼编码

typedef struct 
{
    char cd[N];
    int start;
}HCode;

void CreateHCode(HTNode ht[], HCode hcd[], int n0)
{
    int i, f, c;
    HCode hc;
    for (i = 0; i < n0; i++)
    {
        hc.start = n0; c = i;
        f = ht[i].parent;
        while (f != -f)
        {
            if(ht[f].lchild == c)
                hc.cd[hc.start--] = '0';
            else
                hc.cd[hc.start--] = '1';
            c = f;
            f = ht[f].parent;
        }
        
        
    }
    
}

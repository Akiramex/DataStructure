/**
 * @file 拓扑排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-13
 * 
 * @copyright Copyright (c) 2022
 * 
 * 拖布排序的方法如下：
 * 1.从有向图中选择一个没有前驱（即入度为0）的顶点并且输出它
 * 2.从图中删去该顶点，并且删去从该顶点出发的全部有向边
 * 3.重复上述两步，直到剩余的图中不再存在没有前驱的顶点为止
 * 
 * 拓扑排序可以用来判断一个有向图是否有回路
 */

#include<iostream>
using namespace std;
#define MAXV 50     //最大顶点个数
#define INF 32767
#define InfoType int


//邻接表
typedef struct 
{
    int no; //顶点的编号
    InfoType info;    //顶点的其他信息
}Vertex;
typedef struct ANode
{
    int adjvex; //临边的邻接点编号
    struct ANode *nextarc;  //指向下一条边的指针
    int weight;     //相关信息，如权值
}ArcNode;   //边节点类型
typedef struct Vnode
{
    Vertex data;
    int count;          //入度置初值 0
    ArcNode * firstarc; //指向第一个边界点  
}VNode; //邻接表的头结点类型
typedef struct 
{
    VNode adjlist[MAXV];    //邻接表的头结点数组
    int n, e;   //图中的顶点数 n和边数 e
}AdjGraph;  //完整的图邻接表类型

void TopSort(AdjGraph *G)
{
    int i, j;
    int St[MAXV], top = -1; //栈 St的指针为 top
    ArcNode *p;
    for (i = 0; i < G->n; i++)  //入度置初值 0
        G->adjlist[i].count = 0;
    for (i = 0; i < G->n; i++)  //求所有顶点的入度
    {
        p = G->adjlist[i].firstarc;
        while (p != NULL)
        {
            G->adjlist[p->adjvex].count++;
            p = p->nextarc;
        }
    }
    for (i = 0; i < G->n; i++)  //将入度为 0的点进栈
    {
        if(G->adjlist[i].count == 0)
            {
                top++;
                St[top] = i;
            }
    }
    while (top > -1)    //栈不空循环
    {
        i = St[top]; top--; //出栈一个顶点 i
        printf("%d ",i);
        p = G->adjlist[i].firstarc;
        while (p != NULL)
        {
            j = p->adjvex;
            G->adjlist[j].count--;          //将栈顶 i的出边邻接点的入度减少 1
            if (G->adjlist[j].count == 0)   //将入度为 0的邻接点进栈
            {
                top++;
                St[top] = j;
            }
            p = p->nextarc; //找下一个邻接点
        }
    }
}
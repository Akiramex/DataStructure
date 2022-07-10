/**
 * @file Kruskal.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;
#define MAXV 20
#define MaxSize 20
#define InfoType int
#define INF 32767

//邻接矩阵
typedef struct
{
    int no; //顶点的编号
    InfoType info;    //顶点的其他信息
}VertexType;
typedef struct 
{
    int edges[MAXV][MAXV];  //邻接矩阵数组
    int n, e;               //顶点数，边数 
    VertexType vexs[MAXV];  //存放顶点信息
}MatGraph;  //完整的图邻接矩阵类型


typedef struct 
{
    int u;  //边的起始顶点
    int v;  //边的终止顶点
    int w;  //边的权值
}Edge;

void InsertSort(Edge e[],int n)
{
    int i, j;
    for (i = 1; i < n; i++)
    {
        if(e[i].w < e[i-1].w)
        {
            Edge temp = e[i];
            for (j = i - 1; j >= 0 && temp.w < e[j].w; j--)
            {
                e[j + 1] = e[j];
            }
            e[j + 1] = temp;
        }
    }
}

void Kruskal(MatGraph g)
{
    int i, j, u1, v1, sn1, sn2, k;
    int vset[MAXV]; //检查是否为同一连同分量的数组
    Edge E[MaxSize];

    //用 E 储存图的所有边
    k = 0;
    for (i = 0; i < g.n; i++)
        for (j = 0; j <= i; j++)
        {
            if(g.edges[i][j] != 0 && g.edges[i][j] != INF)
            {
                E[k].u = i;
                E[k].v = j;
                E[k].w = g.edges[i][j];
                k++;
            }
        }
    InsertSort(E,g.n);  //直接插入排序

    //初始化 vest数组
    for (i = 0; i < g.n; i++)
        vset[i] = i;    
    
    k = 1;          //k表示当前构造生成树的第几条边，初值为 1
    j = 0;          //E 中边的下标,初值为 0
    
    while(k < g.n)  //生成的边数小于 n 时循环
    {
        u1 = E[j].u; v1 = E[j].v;   //取一条边的两个顶点
        sn1 = vset[u1];
        sn2 = vset[v1];             //分别得到两个顶点所属的集合编号
        if(sn1 != sn2)              //两顶点属于不同的集合，该边是最小生成树的一条边
        {
            printf("(%d,%d):%d\n", u1, v1, E[j].w);
            k++;                                    //生成边数增 1
            for (i = 0; i < g.n; i++)               //两个集合同一编号
                if(vset[i] == sn2)
                    vset[i] = sn1;
        }
        j++;                                        //扫描下一条边
    }
}
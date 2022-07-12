/**
 * @file Dijkstra.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-12
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
void Dispath(MatGraph g, int dist[], int path[], int S[], int v);   
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

void Dijkstra(MatGraph g, int v)
{
    int dist[MAXV], path[MAXV];
    int S[MAXV];                //S[i] = 1 表示 i在 S中，S[i] = 0表示 i在 U中
    int MINdis, i, j, u;

    for (i = 0; i < g.n; i++)
    {
        dist[i] = g.edges[v][i];    //距离初始化
        S[i] = 0;                   //S数组置空
        if(g.edges[v][i] < INF)     //路径初始化
            path[i] = v;            //顶点 v到顶点 i有边时，置顶点 i的前一个顶点为 v
        else
            path[i] = -1;           //顶点 v到顶点 i没边时，置顶点 i的前一个顶点为 -1
    }
    S[v] = 1; path[v] = 0;

    //循环直到所有顶点的最短路径都求出
    for (i = 0; i < g.n - 1; i++)   
    {
        MINdis = INF;
        for (j = 0; j < g.n ; j++)          //选取不在 S中(即在 U中)且具有最小最短路径长度的顶点 u
            if(S[j] == 0 && dist[j] < MINdis)
            {   u = j;
                MINdis = dist[j];
            }
        S[u] = 1;                               //u 加入S中
        for (j = 0; j < g.n; j++)               //修改不在 S中(即在 U中)的顶点的最短路径
            if( S[j] == 0)
                if( g.edges[u][j] < INF && g.edges[u][j] + dist[u] < dist[j])
                    {
                        dist[j] = g.edges[u][j] + dist[u];
                        path[j] = u;
                    }
    }
    Dispath(g,dist,path,S,v);       //输出最短路径
}

void Dispath(MatGraph g, int dist[], int path[], int S[], int v)
{
    int i, j ,k;
    int apath[MAXV], d;
    for (i = 0; i < g.n; i++)               //循环输出从顶点 v 到 i 的路径
        if(S[i] == 1 && i != v)
        {
            printf("从顶点%d到顶点%d的路径长度为：%d\t路径为：",v,i,dist[i]);
            d = 0, apath[d] = i;            //添加路径上的终点
            k = path[i];
            if(k == -1)                     //没有路径的情况
                printf("无路径\n");
            else
            {
                while (k != v)
                {
                    d++; apath[d] = k;
                    k = path[k];
                }
                d++; apath[d] = v;          //添加路径的起点
                printf("%d",apath[d]);      //先输出起点
                for (j = d - 1; i >= 0; j--)//再输出其他顶点
                {
                    printf(",%d",apath[j]);
                }
                printf("\n");
            }
        }
}
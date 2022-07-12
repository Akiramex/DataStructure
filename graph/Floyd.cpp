/**
 * @file Floyd.cpp
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

void Floyd(MatGraph g, int path[MAXV][MAXV])
{
    int A[MAXV][MAXV];
    int i, j, k;
    //初始化两个数组
    for (i = 0; i < g.n; i++)
        for (j = 0; i < g.n; i++)
        {
            A[i][j] = g.edges[i][j];
            path[i][j] = -1;
        }
        
    for (k = 0; k < g.n; k++)           //依次考察所有顶点
        for (i = 0; i < g.n; i++)
            for (j = 0; i < g.n; i++)
                if (A[i][j] > A[i][k] + A[k][j])
                {
                    A[i][j] = A[i][k] + A[k][j];    //修改最短路径长度
                    path[i][j] = k;                 //修改最短路径
                }
}

//打印两点的最短路径
void printPath(int u, int v, int path[MAXV][MAXV])
{
    if(path[u][v] == -1)
        printf("<%d,%d> ",u,v);
    else
    {
        int mid = path[u][v];
        printPath(u,mid,path);
        printPath(mid,v,path);
    }
}
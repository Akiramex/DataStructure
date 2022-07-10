/**
 * @file Prim.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;
#define MAXV 20
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

void Prim(MatGraph g, int v)
{
    int lowcost[MAXV];
    int closest[MAXV];
    int i, j ,k , MIN;

    //给 lowcost 和 closest 赋初值
    for (i = 0; i < g.n; i++)
    {
        lowcost[i] = g.edges[v][i];
        closest[i] = v;
    }
    
    for (i = 1; i < g.n; i++)   //进行 n - 1次循环
    {
        MIN = INF;
        //找到 (V-U) 中找到离 U 最顶点 k
        for (j = 0; j < g.n; j++)   
            if(lowcost[j] != 0 && lowcost[j] < MIN)
            {
                MIN = lowcost[j];
                k = j;              //保存节点
            }
        printf("边(%d,%d)权为：%d\n", closest[k], k, MIN);      //输出最小生成树的一条边
        lowcost[k] = 0;                                        //标记 k 已经加入 U

        //对 (V-U) 中的顶点 j 进行调整
        for (j = 0; j < g.n; j++)
            if(lowcost != 0 && g.edges[k][j] < lowcost[j])
            {
                lowcost[j] = g.edges[k][j];
                closest[j] = k;                                //修改数组中的信息
            }
    }
}
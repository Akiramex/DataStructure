/**
 * @file graph.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
using namespace std;
#define MAXV 50     //最大顶点个数
#define INF 32767
#define InfoType int


#define MaxSize 50  //队最大长度
#define ElemType int    //自定数据类型 默认为int

/*-------------------------------------顺序队的定义---------------------------------------*/
typedef struct
{
    ElemType data[MaxSize];
    int front,rear; //队头和队尾指针
}SqQueue;

/*---------------------------------环形队基本运算的实现------------------------------------*/
//初始化将rear front置 0
//对头指针 front 循环增 1：front = (front + 1) % MaxSize
//队尾指针 rear 循环增 1：rear = (rear + 1) % MaxSize
//队空条件：rear == front
//队满条件：队尾指针循环增 1时等于对头指针（也就是说进栈时队尾尝试进队一次，若达到队头，就认为队满了，不能进队）
//队满条件：(rear + 1) % MaxSize == front
//队内最多 MaxSize-1个元素

//初始化队列
void InitQueue (SqQueue* &q)
{
    q = (SqQueue*)malloc(sizeof(SqQueue));
    q->front = q->rear = 0;
}

//销毁队列
void DestroyQueue(SqQueue *&q)
{
    free(q);
}

//队列是否为空
bool QueueEmpty(SqQueue *q)
{
    return(q->front == q->rear);
}

//进队列
bool enQueue(SqQueue *&q, ElemType e)
{
    if((q->rear + 1) % MaxSize == q->front) //队满上溢出
        return false;   
    q->rear = (q->rear + 1) % MaxSize;
    q->data[q->rear] = e;
    return true;
}

//出队列
bool deQueue(SqQueue *&q, ElemType &e)
{
    if(q->front == q->rear) //队空下溢出
        return false;
    q->front = (q->front + 1) % MaxSize;
    e = q->data[q->front];
    return true;
}


//图的存储结构定义
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


//邻接表
typedef struct ANode
{
    int adjvex; //临边的邻接点编号
    struct ANode *nextarc;  //指向下一条边的指针
    int weight;     //相关信息，如权值
}ArcNode;   //边节点类型

typedef struct Vnode
{
    InfoType info;  //顶点的其他信息InfoType
    ArcNode * firstarc; //指向第一个边界点  
}VNode; //邻接表的头结点类型
typedef struct 
{
    VNode adjlist[MAXV];    //邻接表的头结点数组
    int n, e;   //图中的顶点数 n和边数 e
}AdjGraph;  //完整的图邻接表类型

//--------------------------------------------图的基本算法设计-------------------------------------
//1、创建图的运算算法
//  根据邻接矩阵 A、顶点 n、和边数 e创建图的邻接表 G
void CreateAdj(AdjGraph *& G, int A[MAXV][MAXV], int n, int e)
{
    int i, j;
    ArcNode *p;
    G =(AdjGraph*)malloc(sizeof(AdjGraph));
    for (i = 0; i < n; i++)                     //给邻接表中的所有头结点的指针域置初值
        G->adjlist[i].firstarc = NULL;
    for (i = 0; i < n; i++)                     //检查邻接矩阵中的每个元素
        for(j = n - 1; j >= 0; j--)
            if(A[i][j] != 0 && A[i][j] != INF)  //存在一条边
            {
                p = (ArcNode *)malloc(sizeof(ArcNode));
                p-> adjvex = j;                     //存放邻接点
                p->weight = A[i][j];

                p->nextarc = G->adjlist[i].firstarc;//头插法插入节点p
                G->adjlist[i].firstarc = p;
            }
    G->n = n; G->e = e;
}

//2、输出图的运算算法
void DestroyAdj(AdjGraph *& G)
{
    int i;
    ArcNode *p;
    for (i = 0; i < G->n; i++)
    {
        p = G->adjlist[i].firstarc;
        printf("%3d: ", i);
        while(p != NULL)
        {
            printf("%3d[%d]->", p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("^\n");
    }
}

//3、销毁图的运算算法
void DestroyAdj(AdjGraph *&G)
{
    int i;
    ArcNode *pre, *p;
    for (i = 0; i < G->n; i++)
    {
        pre = G->adjlist[i].firstarc;
        if(pre != NULL)
        {
            p = pre->nextarc;
            while (p != NULL)       //释放第 i个单链表的所有边节点
            {
                free(p);
                pre = p;
                p = p->nextarc;
            }
            free(pre);
        }
        free(G);                    //释放头结点数组
    }
}

//4、邻接表转邻接矩阵
//假设初始时邻接矩阵 g中所有主对角元素为 0，其他元素为 INF
void MatToList(MatGraph g, AdjGraph*& G)
{
    int i;
    ArcNode *p;
    for (i = 0; i < G->n; i++)
    {
        p = G->adjlist[i].firstarc;
        while (p != NULL)
        {
            g.edges[i][p->adjvex] = p->weight;
            p = p->nextarc;
        }
    }
    g.e = G->e; g.n = G->n;
}

//深度优先遍历 DFS
//设置一个全局变量 visited[],当顶点 i被访问过时，数组中的元素visited[i]置为 1，否则置为 0
int visited[MAXV] = {0};
void DFS(AdjGraph *G, int v)
{
    ArcNode *p;
    visited[v] = 1;             //置已访问标记
    printf("%d ", v);
    p = G->adjlist[v].firstarc; //p指向顶点 v的第一个邻接点
    while (p != NULL)
    {
        if(visited[p->adjvex] == 0) //若 p->adjvex 顶点未被访问，递归访问它
            DFS(G, p->adjvex);
        p = p->nextarc;             //p指向顶点 v的下一邻接点
    }
}

//广度优先遍历 DFS
//在 DFS时需要用到一个队列，这里采用环形队列，以类似于二叉树的层次遍历方式来遍历图
void BFS(AdjGraph * G,int v)
{
    int w, i;
    int vIsited[MAXV];
    ArcNode *p;
    SqQueue *qu;
    InitQueue(qu);

    for (i = 0; i < MAXV; i++)          //初始化顶点访问标记数组
        vIsited[i] = 0;

    printf("%2d",v);                    //输出被访问顶点的编号
    vIsited[v] = 1;

    enQueue(qu,v);
    while(!QueueEmpty(qu))
    {
        deQueue(qu,w);
        p = G->adjlist[w].firstarc;     //指向 w的第一个邻接点
        while(p != NULL)                //查找w所有的邻接点
        {
            if(vIsited[p->adjvex] == 0)
            {
                vIsited[p->adjvex] = 1;
                printf("%2d",p->adjvex);
                enQueue(qu,p->adjvex);
            }
            p = p->nextarc;             //找下一个邻接点
        }
    }
    printf("\n");
}


/**
 * @file mg_Sqstack.c
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//用顺序栈求解迷宫问题
#include <stdlib.h>
#include <stdio.h>
#define M 8
#define N 8
#define MaxSize 50
static int mg[M+2][N+2] = 
{
    {1,1,1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},{1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},{1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},{1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1}
};
typedef struct {
    int i;  //当前方块的行号
    int j;  //当前方块的列号   
    int di; //di 是下一相邻可走方位的方位号
}Box;
typedef struct {
    Box data[MaxSize];
    int top;    //栈顶指针
}StType;

void InitStack(StType *&s)
{
    s = (StType*)malloc(sizeof(StType));
    s->top = -1;
}
bool Push(StType*&s, Box e)
{
    if(s->top == MaxSize -1) return false;
    s->top++;
    s->data[s->top] = e;
    return true;
}
bool Pop(StType*&s, Box &e)
{
    if(s->top == -1) return false;
    e = s->data[s->top];
    s->top--;
    return true;
}
bool GetTop(StType*s, Box &e)
{
    if(s->top == -1) return false;
    e = s->data[s->top];
    return true;
}
bool StackEmpty(StType* s)
{
    return(s->top == -1);
}
bool DestroyStack(StType *&s)
{
    free(s);
}
bool mgpath(int xi, int yi, int xe, int ye) //求解路线为 (xi,yi)->(xe,ye)
{
    Box path[MaxSize], e;
    int i, j, di, i1, j1, k;
    int cnt;
    bool find;
    StType *st;
    InitStack(st);
    e.i = xi; e.j = yi; e.di = -1;
    Push(st,e); //将起点进栈
    mg[xi][yi] = -1;    //将迷宫值置为 -1，避免重复走该方块
    while (!StackEmpty)     //当栈不为空循环
    {
        GetTop(st,e);   //取出栈顶元素
        i = e.i; j = e.j; di = e.di;
        if(i == xe && j == ye)  //当栈顶元素为迷宫终点
        {
            printf("一条迷宫路径如下：\n");
            k = 0;
            while(!StackEmpty)
            {
                Pop(st,e);
                path[k++] = e;
            }
            while(k >= 1)
            {
                k--;
                printf("\t(%d,%d)",path[k].i,path[k],j);
                cnt++;
                if(cnt % 5 == 0)    //每 5个方块换一行
                    printf("\n");
            }
            printf("\n");
            DestroyStack(st);
            return true;    
        }
        //取出的栈顶元素不是终点
        find = false;   //下一相邻可走方块的标志位
        while (di <= 4 && !find)
        {
            di++;
            switch (di)
            {
            case 0: i1 = i - 1; j1 = j; break;
            case 1: i1 = i; j1 = j + 1; break;
            case 2: i1 = i + 1; j1 = j; break;
            case 3: i1 = i; j1 = j - 1; break;
            }
            if(mg[i1,j1] == 0) find = true; //按0-3顺序找，找到了令标志位为真
        }
        if(find)    //找到相邻可走方块
        {
            st->data[st->top].di = di;  //修改原栈顶元素的 di值
            e.i = i1; e.j = j1; e.di = -1;
            Push(st,e); 
            mg[i1][j1] = -1;    
        }
        else    //没有找到相邻可走方块
        {
            Push(st,e); //栈顶元素出栈
            mg[e.i][e.j] = 0;   //让退栈方块的位置值（迷宫值）变为可走方块
        }
    }
    //栈空，循环结束，说明已没有可走路径
    DestroyStack(st);
    return false;
}
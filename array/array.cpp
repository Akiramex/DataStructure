/**
 * @file array.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//利用数组解决约瑟夫问题
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
void josephus(int n, int m)
{
    int p[MaxSize];
    int i, j, t;
    for (i = 0; i < n; i++)
    {
        p[i] = i + 1; 
    }
    
    t = 0;  //首次报数的起始位置z
    for(i = n; i >= 1; i--) // i表示当前的人数，出列一次，人数减少 1
    {
        t = (t + m - 1) % i;//t表示出列者的编号
        printf("%d ",p[t]);
        for (j = t + 1; j <= i - 1; j++)
        {
            p[j-1] = p[j];  //前移一位覆盖已出列的元素
        }
    }
    printf("\n");
}
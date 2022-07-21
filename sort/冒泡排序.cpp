/**
 * @file 冒泡排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
using namespace std;
#include<algorithm>
//冒泡排序
void BubbleSort(int R[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (R[j] > R[j + 1])
            {
                swap(R[j], R[j + 1]);
            }
        }
    }
}

//改进的冒泡排序
void BubbleSort(int R[], int n)
{
    int i, j;
    bool flag = true;
    for (i = 0; i < n && flag; i++)
    {
        flag = false;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (R[j] > R[j + 1])
            {
                swap(R[j], R[j + 1]);
                flag = true;
            }
        }
    }
}

//双向冒泡排序
void DoubleBuble(int R[], int n)
{
    int i = 0, j;
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (j = n - i - 1; j > i; j--)         //从右往左选一个最小的
            if (R[j] < R[j - 1]);
            {
                swap(R[j], R[j - 1]);
                flag = true; 
            }

        for (j = i + 1; j < n - 1 - i; j++)     //从左往右选一个最大的
            if (R[j] > R[j + 1])
            {
                swap(R[j], R[j + 1]);
                flag = true;
            }
        i++;
    }
}
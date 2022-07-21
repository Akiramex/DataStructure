/**
 * @file 直接插入排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;

//已经排好序的部分 有序区， 未排序的部分 无序区
//直接插入排入的逻辑：开始有 第1位元素在有序区，因为单个元素必定有序，然后在无序区选取一位元素，在有序区依次比较，找到自己的位置，反复，直到排序完成
void InsertSort(int R[], int n)
{
    int i, j;
    for (i = 1; i < n; i++)
    {
        if(R[i] < R[i - 1])
        {
            int temp = R[i];
            for (j = i - 1; j >= 0 && R[j] > temp; j--)
            {
                R[j + 1] = R[j];
            }
            R[j + 1] = R[i];
        }
    }
}
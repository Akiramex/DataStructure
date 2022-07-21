/**
 * @file 选择排序.cpp
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
void SelectSort(int R[], int n)
{
    int i, j, k;
    for (i = 0; i < n - 1; i++)
    {
        k = i;
        for (j = i + 1; j < n; j++)
        {
            if (R[j] < R[k])
                k = j;
        }
        if (k != i)
            swap(R[i],R[k]);
    }
    
}
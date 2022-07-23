/**
 * @file 二路归并排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;

//假设两个有序表存放在同一数组的相邻位置，将两段有序表 R[low..mid],R[mid+1..high]归并成一个有序表
void Merge(int R[], int low, int mid, int high)
{
    int *R1;
    int i = low, j = mid + 1, k = 0;    //i,j,k分别为第1，2段，R1的起始下标
    R1 = (int*)calloc(high - low + 1, sizeof(int)); //分配堆空间
    while (i <= mid && j <= high)
    {
        if (R[i] <= R[j])
        {
            R1[k] = R[i];
            i++; k++;
        }
        else
        {
            R1[k] = R[j];
            j++; k++;
        }
    }
    while (i <= mid)
    {
        R1[k] = R[i];
        i++; k++;
    }
    while (j <= high)
    {
        R1[k] = R[j];
        j++; k++;
    }
    for (k = 0, i = low; i <= high; i++, k++)
        R[i] = R1[k];
    free(R1);
}

void MergePass(int R[], int length, int n)  //length是一段有序表的长度，n是整个表的长度
//R[0..length-1],R[Length..2Length-1],...R[(n/Length)*Length..n-1]
//若子表的个数为奇数，最后一个子表轮空，若子表的个数为偶数，最后一个子表的元素个数区间上限为 n-1.
{  //对整个排序表进行一趟归并
    int i;
    for (i = 0; i + 2 * length - 1 < n; i = i + 2 * length) //归并 length长的两相邻子表
        Merge(R,i,i+length-1,i+2*length-1);
    if(i+ length - 1 < n - 1)                   //余下两个子表，后者长度小于length
        Merge(R,i,i+length-1,n-1);
}

void MergeSort(int R[], int n)
{
    int length;
    for (length = 1; length < n; length = 2 * length)   //进行log2N趟归并
        MergePass(R,length,n);
}
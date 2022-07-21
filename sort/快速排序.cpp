/**
 * @file 快速排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
void QuickSort(int R[],int start, int end)
{
    int i = start;
    int j = end;
    int base = R[i];    //基准数
    while(i < j)
    {
        while (j > i && R[j] > base)    //从右往左扫描，找一个小于base的数
            j--;
        R[i] = R[j];
        while (j > i && R[i] < base)    //从左往右扫描，找一个小于base的数
            i++;
        R[j] = R[i];
    }
    R[i] = base;                        //归位基准数
    QuickSort(R, start, i - 1);         //左区间递归
    QuickSort(R, i + 1, end);           //右区间递归
}
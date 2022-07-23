/**
 * @file 堆排序.cpp
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
//不稳定
//筛选算法
void sift(int R[], int low, int high)
{
    int i = low, j = 2 * i;     //i指向被筛选节点，j指向 i 的左孩子
    int temp = R[i];            //保存被筛选节点的关键值
    while (j <= high)           //在树内元素循环
    {
        if(j < high && R[j] < R[j + 1]) //当存在右孩子，且右孩子比左孩子大时，j指向右孩子
            j++;
        if(R[j] > temp)                 //孩子节点 大于 被筛选节点
        {
            R[i] = R[j];
            i = j;
            j = i * 2;
        }
        else
            break;
    }
    R[i] = temp;
}

/*
构建初始堆R[1..n]的过程是，对一棵完全二叉树，从最后一个分支节点到根节点。反复使用sift算法。大者上浮，小者下沉
for(i = n / 2; i >= 1; i--)
    sitf(R,i,n);

每次运行完筛选算法，头节点必定是最大的元素，将头结点与最后一个节点换位，这样有序区就找到一个元素
*/

void HeapSort(int R[], int n)
{
    int i;
    for (i = n / 2; i >= 1 ; i--)       //创建初始堆
        sift(R,i,n);                
    for (i = n; i >= 2; i--)
    {
        swap(R[1],R[i]);
        sift(R,1,i-1);
    }
}
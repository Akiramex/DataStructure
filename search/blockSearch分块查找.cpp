/**
 * @file blockSearch分块查找.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
#define MAXI 20 //索引表的最大长度
#define KeyType int //关键字的类型

typedef struct 
{
    KeyType key;
    int link;   //指向对应块的起始下标
}IdxType;

//采用二分查找索引表的分块查找算法  (索引表 I的长度为 b)
int IdxSearch(IdxType I[], int b, int R[], int n, KeyType k)
{
    int s = (n + b - 1) / b;    //向上取整
    int low = 0, high = b - 1, mid ,i;
    while (low <= high)         //二分查找,找到的位置是 high + 1;
    {
        mid = low + (high - low)/2;
        if (I[mid].key > k)
            high = mid -1;
        else
            low = mid + 1;
    }
    //在索引块 high+1 中查找
    i = I[high + 1].link;   //索引块的起始位置
    while (i <= I[high + 1].link + s - 1 && R[i] != k)
        i++;
    if(i <= I[high + 1].link + s - 1)   //查找成功，返回逻辑序号
        return i+1;
    else
        return 0;
}
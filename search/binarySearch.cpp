/**
 * @file binarySearch.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
#include<vector>
using namespace std;

//方法一，左闭右闭的区间
int BinarySearch1(vector<int> &num, int target)
{
    int left = 0, right = num.size() - 1;
    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        if (num[middle] > target)
            right = middle - 1;
        else if (num[middle] < target)
            left = middle + 1;
        else return middle;
    }
    return -1;
}

//方法一，左闭右开的区间
int BinarySearch2(vector<int> &num, int target)
{
    int left = 0, right = num.size();
    while (left < right)
    {
        int middle = left + (right - left) / 2;
        if (num[middle] > target)
            right = middle;
        else if (num[middle] < target)
            left = middle + 1;
        else return middle;
    }
    return -1;
}
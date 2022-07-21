/**
 * @file 折半插入排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//折半插入的逻辑：类似于直接插入排序，只不过是在寻找插入位置时。使用二分查找而非顺序查找,找到的位置是 high+1

void BinInsertSort(int R[], int n)
{
    int i, j, low, high, mid;
    int temp;
    for (i = 1; i < n; i++)
    {
        if (R[i] > R[i + 1])
        {
            temp = R[i];
            low = 0; high = i - 1;
            while (low <= high)
            {
                mid = low + (high - low) / 2;
                if (temp < R[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            for (j = i - 1; j >= high + 1; j--)
            {
                R[j + 1] = R[j];
            }
            R[high + 1] = temp;
        }
    }
}
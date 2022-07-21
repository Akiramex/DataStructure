/**
 * @file 希尔排序.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//不稳定排序
//分组的插入排序
void ShellSort(int R[], int n)
{
    int i, j, d;
    int temp;
    d = n / 2;
    while (d > 0)
    {
        for (i = d; i < n; i++)
        {
            temp = R[i];
            for (j = i - d; j >= 0 && R[j] > temp; j--)
            {
                R[j + d] = R[j];
            }
            R[j + d] = temp;
        }
        d = d/2;
    }
}
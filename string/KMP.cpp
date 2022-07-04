/**
 * @file KMP.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define SqString string
#define MaxSize 50

void GetNext(SqString t, int next[])
{
    int j , k;
    j = 0; k = -1;
    next[0] = -1;
    while(j < t.size() - 1)
    {
        if(k == -1 || t[j] == t[k])
        {
            j++;k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
}

void GetNextval(SqString t, int nextval[])
{
    int j , k;
    j = 0; k = -1;
    nextval[0] = -1;
    while(j < t.size() - 1)
    {
        if(k == -1 || t[j] == t[k])
        {
            j++;k++;
            if(t[j] != t[k])
                nextval[j] = k;
            else
                nextval[j] = nextval[k];
        }
        else
        {
            k = nextval[k];
        }
    }
}
int KMPIndex(SqString s, SqString t)
{
    int next[MaxSize], i = 0, j = 0;
    GetNext(t,next);
    while (i < s.size() && j < t.size())
    {
        if(j == -1 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if(j >= t.size())
        return(i - t.size());
    else
        return -1;
}

int main()
{
    string t ="aaabaaab";
    int arr[10] = {0};
    GetNext(t,arr);
    for(int i = 0; i < 10; i++)
    {
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
    GetNextval(t,arr);
    for(int i = 0; i < 10; i++)
    {
        cout<<arr[i]<<"\t";
    }
    return 0;
} 
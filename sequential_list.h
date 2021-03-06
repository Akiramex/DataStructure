/**
 * @file sequential_list.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    sequential_list 顺序表
*/
#include <stdlib.h>
#include <stdio.h>
#define MaxSize 50  //顺序表最大长度
#define ElemType int    //自定数据类型

/*-------------------------------------顺序表的定义------------------------------------------*/

typedef struct
{
    ElemType data[MaxSize]; //存放线性表的元素
    int length;
}SqList;


/*-------------------------------------创建顺序表---------------------------------------*/
//创建顺序表
void CreateList(SqList* &L, ElemType a[], int n)    //由 a中 n个元素建立顺序表
{
    int i = 0, k =0;    //k 表示 L中元素个数，初始值为 0
    L =(SqList*)malloc(sizeof(SqList)); //开辟内存至堆区
    while (i < n)
    {
        L->data[k] = a[i];
        k++,i++; 
    }
    L->length = k;  //设置长度为 k
}



/*-----------------------------------顺序表基本运算的实现-------------------------------------*/
//初始化顺序表
void InitList(SqList* &L)
{
     L =(SqList*)malloc(sizeof(SqList)); //开辟内存至堆区
     L->length = 0;
}

//销毁顺序表
void DestroyList(SqList* &L)
{
    free(L);
}

//判断顺序表是否为空表
bool ListEmpty(SqList* L)
{
    return(L->length == 0);
}

//求线性表的长度
int ListLength(SqList* L)
{
    return(L->length);
}

//输出顺序表
void DispList(SqList* L)
{
    for (int i = 0; i < L->length; i++)
        printf("%d ",L->data[i]);
    printf("\n");
}

//求某个元素值
bool GetElem(SqList* L, int i, ElemType &e)
{
    if(i < 1 || i > L->length)  //合法性检查
        return false;
    e = L->data[i-1];
    return true;
}

//按元素查找
int LocateElem(SqList* L, ElemType e)
{
    int i = 0;
    while(i < L->length && L->data[i] != e)
    i++;    //查找元素
    if(i >= L->length)  //未找到时返回 0
        return 0;
    else
        return i+1; //返回逻辑序号
}

//插入元素
bool ListInsert(SqList* &L, int i, ElemType e)
{
    int j;
    if(i < 1 || i > L->length + 1 || L->length == MaxSize)  //合法性检查
        return false;
    i--;    //将逻辑序号转为物理序号
    for (j = L->length; j > i; j--) //将元素后移
        L->data[j] = L->data[j-1];
    L->data[i] = e;
    L->length++;    //长度加 1
    return true;
}

//删除元素
bool ListDelete(SqList* &L, int i, ElemType e)
{
    int j;
    if(i < 1 || i > L->length)  //合法性检查
        return false;
    i--;    //将逻辑序号转化为物理序号
    e = L->data[i];
    for(j = i; j < L->length-1; j++)
        L->data[j] = L->data[j+1];
    L->length--;    //长度减 1
    return true;
}

/*---------------------------------------实际例题-----------------------------------------*/

//设计一个算法，删除顺序表中所有值等于 x的元素，要求算法的时间复杂度为 O(n),空间复杂度为 O(1)
//方法一：快慢指针（双指针）
void delnode1(SqList* &L, ElemType x)
{
    int i, k=0; //k记录不等于 x的元素的个数，即要插入元素的个数
    for (i = 0; i < L->length; i++)
        if(L->data[i] != x)
        {
            L->data[k] = L->data[i];
            k++;
        }
    L->length = k;
}

//方法二： 单指针
void delnode2(SqList* &L, ElemType x)
{
    int i,k=0;  //k记录等于 x的元素的个数
    for (i = 0; i < L->length; i++)
    {
        if(L->data[i] == x) //当前元素为 x时，k加 1
            k++;
        else
            L->data[i-k] = L->data[i];  //当前元素不为 x时，元素向前移 k位
    }
    L->length = L->length -k;
}


/*设计一个尽可能高效的算法，使顺序表第一个元素为基准，将所有小于等于它的元素移到该基准的前面，将所有
大于它的元素移到基准的后面*/
void swap(ElemType &a, ElemType &b)
{
    ElemType temp;
    temp = a;
    a = b;
    b = temp; 
}
//方法一 swap
void partition1(SqList* &L)
{
    int i = 0, j = L->length-1;
    ElemType pivot = L->data[0];    //保存基准
    while(i < j)    //从区间左右交替向中间扫描，直到 i=j
    {
        while(i < j && L->data[j] > pivot)  //从右向左扫描，找一个比基准小的数
            j--;
        while(i < j && L->data[i] <= pivot) //从左向右扫描，找一个比基准大的数
            i++;
        if(i < j)
            swap(L->data[i],L->data[j]);
    }
    swap(L->data[0],L->data[i]);
}

//方法二 覆盖（交换次数更少）
void partition2(SqList* &L)
{
    int i = 0, j = L->length-1;
    ElemType pivot = L->data[0];    //保存基准
    while(i < j)    //从区间左右交替向中间扫描，直到 i=j
    {
        while(i < j && L->data[j] > pivot)
            j--;
        L->data[i] = L->data[j];    //覆盖
        while(i < j && L->data[i] <= pivot)
            i++;
        L->data[j] = L->data[i];    //覆盖
    }
    L->data[i] = pivot;
}

//设计一个算法，将所有奇数移动到偶数的前面。
//方法一 swap
void move1(SqList* &L)
{
    int i = 0, j = L->length-1;
    while(i < j)
    {
        while(i < j && L->data[j] %2 == 0)
            j--;
        while(i < j && L->data[i] %2 == 1)
            i++;
        if(i < j)
            swap(L->data[i], L->data[j]);
    }
}

//方法二 区间
void move2(SqList* &L)
{
    int i = -1, j;  //i表示奇数区间的长度。
    for (j = 0; i < L->length; j++) //循环至队尾
        if(L->data[j] %2 == 1)  //j指向奇数时
        {
            i++;
            if(i < j)//若 j大于 i
                swap(L->data[i], L->data[j]);
        }
}

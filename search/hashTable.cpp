/**
 * @file hashTable.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//线性探查法建立哈希表

#include<iostream>
using namespace std;

#define NULLKEY -1  //定义空关键字值
#define DELKEY -2   //定义被删关键字值
typedef int KeyType;    //关键字类型
typedef struct {
    KeyType key;    //关键字域
    int count;      //探测次数域
}HashTable;

//1、插入
// ha[]哈希表, n哈希表元素个数，m哈希表长度, p除留余数法的系数
void InsertHT(HashTable ha[], int &n, int m, int p, KeyType k)
{
    int i, adr;
    adr = k % p;    //计算哈希函数值
    if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
    {
        ha[adr].key = k;
        ha[adr].count = 1;
    }
    else            //发生冲突时，采用线性探查法解决冲突
    {
        i = 1;
        do
        {
            adr = (adr + 1) % m;
            i++;
        } while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);
        ha[adr].key = k;
        ha[adr].count = i;
    }
    n++;            //哈希表中的总元素个数增 1
}

//2、建表
void CreateHT(HashTable ha[], int &n, int m, int p, KeyType keys[], int n1)
//由关键字序列 keys[](共有 n1个元素) 创建哈希表
{
    for (int i = 0; i < m; i++) //哈希表置空
    {
        ha[i].key = NULLKEY;
        ha[i].count = 0;
    }
    n = 0;
    for (int i = 0; i < n1; i++)
        InsertHT(ha, n, m, p, keys[i]);
    
}

//3、删除元素
bool DeleteHT(HashTable ha[], int&n, int m, int p, KeyType k)
{
    int adr;
    adr = k % p;
    while (ha[adr].key != NULLKEY && ha[adr].key != k)  //线性探查
        adr = (adr + 1) % m;
    if (ha[adr].key == k)       //查找成功
    {
        ha[adr].key = DELKEY;   //逻辑删除
        return true;
    }
    else                        //查找失败
        return false;
}

//4、查找
void SearchHT(HashTable ha[], int m, int p, KeyType k)
{
    int i = 1, adr;
    adr = k % p;
    while (ha[adr].key != k && ha[adr].key != NULLKEY)
        {
            i++;                    //累计关键字的比较次数
            adr = (adr + 1) % m;
        }
    if (ha[adr].key == k)
        printf("成功：关键字%d，比较%d次\n,k,i");
    else
        printf("失败：关键字%d，比较%d次\n,k,i");
}

//5、ASL平均查找长度
void ASL(HashTable ha[], int n, int m, int p)
{
    int i, j;
    int succ = 0, unsucc = 0, s;
    for (i = 0; i < m; i++)
        if(ha[i].key != NULLKEY)
            succ = succ + ha[i].count;  //累计成功时总关键字比较次数
    printf("成功情况下ASL(%d)=%g\n",n,succ*1.0/n);

    for (i = 0; i < m; i++)
    {
        s = 1; j = 1;
        while(ha[j].key != NULLKEY)
        {
            s++;
            j = (j + 1) % m;
        }
        unsucc = unsucc + s;            //累计不成功时总关键字比较次数
    }
    printf("不成功情况下ASL(%d)=%g\n",n,unsucc*1.0/p);
}
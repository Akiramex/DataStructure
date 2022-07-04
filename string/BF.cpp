/**
 * @file BF.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//串的匹配模式，BF简单匹配算法，这里使用内置string结构代替，自定顺序串Sqstring
#include<iostream>
using namespace std;
#define SqString string

int BF(SqString s, SqString t)
{
    int i, j;
    while(i < s.size() && j < t.size())
    {
        if(s[i] == t[j])    //比较两字符相同
        {
            i++; j++;       //依次比较后面的字符
        }
        else                //字符不同
        {
            i = i - j + 1;  //s字串向位移
            j = 0;
        }
    }
    if(j >= t.size())  return(i - t.size());   //j超界，表示 t是 s的字串，返回 t在 s中的位置
    else return(-1);    //匹配失败
}

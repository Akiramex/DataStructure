/**
 * @file sequential_stack.h
 * @author Akira
 *
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    sequential stack 顺序栈
    + 栈空的条件：s->top = -1
    + 栈满的条件：s->top = MaxSize - 1
    + 元素 e的进栈操作：先将栈顶指针 top增 1。然后将元素 e放在栈顶指针处
    + 出栈操作：先将栈顶指针 top处的元素取出放在 e 中，然后将栈顶指针减少 1
*/

#include <stdlib.h>
#include <stdio.h>
#define MaxSize 50  //顺序表最大长度
#define ElemType int    //自定数据类型

/*-------------------------------------顺序表的定义---------------------------------------*/
typedef struct{
    ElemType data[MaxSize];
    int top;    //栈顶指针
}SqStack;

/*---------------------------------顺序表基本运算的实现------------------------------------*/
//初始化栈
void InitStack(SqStack* &s)
{
    s = (SqStack*)malloc(sizeof(SqStack));
    s->top = -1;
}

//销毁栈
void DestoryStack(SqStack* &s)
{
    free(s);
}

//判断栈是否为空
bool StackEmpyt(SqStack *s)
{
    return(s->top == -1);
}

//进栈
bool Push(SqStack* &s, ElemType e)
{
    if(s->top == MaxSize - 1) return false; //栈满的情况
    s->top++;   //栈顶指针增 1
    s->data[s->top] = e;
    return true;
}

//出栈
bool Pop(SqStack* &s, ElemType &e)
{
    if(s->top == -1) return false;  //栈空的情况
    e = s->data[s->top];    //保存出栈元素
    s->top--;   //栈顶指针减 1
    return true;
}

bool GetTop(SqStack* s, ElemType &e)
{
    if(s->top == -1) return false;  //栈空的情况
    e = s->data[s->top];
    return true;
}
/*---------------------------------------实际例题-----------------------------------------*/
//利用顺序栈判断一个字符串是否为对称串。所谓堆成串指从左向右读和从右向左读的序列相同
//设计思路：将字符串全部进栈再依次出栈，与原字符串比较
bool symmetry(ElemType str[])
{
    int i; ElemType e;
    SqStack *st;
    for (i = 0; str[i] != '\0'; i++) {  //所有元素进栈
        Push(st,str[i]);
    }
    for (i = 0; i < str[i] != '\0'; i++) {
        Pop(st, e); //依次出栈
        if(str[i] != e) {   //若 e与当前串字符不同表示不是对称串
            DestoryStack(st);   //销毁栈
            return false;
        }
        DestoryStack(st);   //销毁栈
        return true;    
    }
}

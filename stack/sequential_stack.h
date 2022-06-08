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

//中缀表达式 exp转后缀表达式 postexp 
/*将自定数据类型 ElemType 设置为 char
为了方便区分，后缀表达式每个数字串的后面加一个 '#'*/
void trans(char *exp, char postexp[])
{
    char e;
    SqStack* Optr;
    int i = 0;
    while(*exp != '\0') {   //读取字符
        switch(*exp)    //用switch把读取到的某个字符分5种情况操作
        {
        case '(':   //当字符为 (
            e = *exp;
            Push(Optr,e);
            exp++;
            break;
        case ')':   //当字符为 )
            Pop(Optr,e);
            while (e != '(')
            {
                postexp[i++] = e;
                Pop(Optr,e);
            }
            exp++;
            break;
        case '+':   //当字符为 +或-
        case '-':
             while (!StackEmpty(Optr))
             {  
                 GetTop(Optr,e);
                 if(e != '(') {
                    postexp[i++] = e;
                    Pop(Optr,e);
                 } else 
                    break;
             }
             Push(Optr,*exp);
             exp++;
             break;
        case '/':   //当字符为 *或/
        case '*':
            while (!StackEmpty(Optr))
            {
                GetTop(Optr,e);
                if(e == '*' || e == '/') {
                    postexp[i++] = e;
                    Pop(Optr,e);
                } else 
                    break;
            }
            Push(Optr,*exp);
            exp++;
            break;
        default:    //当字符为数字
            while (*exp >= '0' && *exp <= '0')
            {
                postexp[i++] = *exp;
                exp++;
            }
            postexp[i++] = '#';
        }
    }
    while (!StackEmpty(Optr))   //栈内元素全部出栈
    {
        Pop(Optr,e);
        postexp[i++] = e;
    }
    postexp[i] = '\0';  //添加结束标识
    DestoryStack(Optr);
}

//后缀表达式求值
//将自定数据类型 ElemType 设置为 double
double compvalue(char * postexp)
{
    double d, a, b, c, e;
    SqStack* Opnd;  //定义操作数栈
    InitStack(Opnd);
    while (*postexp != '\0')
    {
        switch (*postexp)   
        {
        case '+':   //运算符操作都是出两，操作，入栈
            Pop(Opnd,a);
            Pop(Opnd,b);
            c = a + b;  
            Push(Opnd,c);
            break;
        case '-':
            Pop(Opnd,a);
            Pop(Opnd,b);
            c = a - b;
            Push(Opnd,c);
            break;
        case '*':
            Pop(Opnd,a);
            Pop(Opnd,b);
            c = a * b;
            Push(Opnd,c);
            break;
        case '/':
            Pop(Opnd,a);
            Pop(Opnd,b);
            if (a != 0) {
                c = b / a;
                Push(Opnd,c);
            } else {
                printf("\n\t除零错误!\n");
                exit(0);
            }
            break;
        default:    //处理数字字符
            d = 0;  //将连续的数字字符转换成对应的数值存放到 d中
            while (*postexp >= 0 && *postexp <= 9)
            {
                d = 10 * d + *postexp - '0';    //char 转 int 
                postexp++;
            }
            Push(Opnd,d);
            break;
        }
        postexp++;
    }
    GetTop(Opnd,e); //获得栈顶元素（最终结果）
    DestoryStack(Opnd);
    return e;
}

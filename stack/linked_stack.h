/**
 * @file linked_stack.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    linked stackt 链栈
    + 栈空的条件：s->next = NULL
    + 栈满的条件：在内存充足下，不存在栈满的情况
    + 元素 e的进栈操作：插入头结点之后
    + 出栈操作：取出首节点的 data值并将其删除
*/
#include <stdlib.h>
#include <stdio.h>
#define ElemType char    //自定数据类型

/*--------------------------------------链栈的定义---------------------------------------*/
typedef struct linknode {
    ElemType data;
    struct linknode *next;
}LinkStNode;

/*----------------------------------链栈基本运算的实现------------------------------------*/
//初始化栈
void InitStack(LinkStNode* &s)
{
    s = (LinkStNode*)malloc(sizeof(LinkStNode));
    s->next = NULL;
}

//销毁栈
void DestroyStack(LinkStNode* &s)
{
    LinkStNode *pre = s, *p =s->next;   //pre指向头节点，p指向首节点
    while(p != NULL) {
        free(pre);  //同步后移
        pre = p;
        p = p->next;
    }
    free(pre);
}

//判断栈是否为空
bool StackEmpty(LinkStNode* s) 
{
    return(s->next == NULL);
}

//进栈
void Push(LinkStNode* &s, ElemType e)
{
    LinkStNode *p;
    p = (LinkStNode*)malloc(sizeof(LinkStNode));
    p->data = e;
    p->next = s->next;
    s->next = p;
}
//出栈
bool Pop(LinkStNode* &s, ElemType &e)
{
    LinkStNode *p;
    if(s->next == NULL) return false;   //栈空的情况下
    p = s->next;
    e = p->data;
    s->next = p->next;
    free(p);
    return true;
}

//取栈顶元素
bool GetTop(LinkStNode *s, ElemType &e)
{
    if(s->next == NULL) return false;   //栈空的情况下
    e = s->next->data;
    return true;
}

/*---------------------------------------实际例题-----------------------------------------*/
//设计一个算法判断输入的表达式中括号是否配对（假设只有'('、')'）
bool Match(char exp[], int n)
{
    int i;
    char e;
    bool match = true;  //匹配标志位，默认为 匹配
    LinkStNode *st;
    InitStack(st);
    for (i = 0; i < n && match; i++) {   //遍历字符串
        if(exp[i] == '(') { //如果字符为左括号，进栈
            Push(st,exp[i]);
        } else if(exp[i] == ')') {  //如果字符为右括号
            if(GetTop(st,e) == NULL) {  //成功取栈顶元素 e
                if(e != '(')
                    match = false;
                else {
                    Pop(st,e);
                }
            }
        }
    }
    if(!StackEmpty) match = false;
    DestroyStack(st);
    return match;
}

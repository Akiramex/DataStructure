/**
 * @file circular_linked_list.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    circular linked list 循环链表
    循环链表有循环单链表和循环双链表两种类型，各自的结点类型与各自链表一样

    单链表->循环单链表：将尾指针的 next域指向头节点
    双链表->循环双链表：将尾指针的 next域指向头指针，头指针的 piror域指向尾指针
    双链表判断队尾的条件是 p->next = L, 另外循环双链表可以通过 p->prior快速找到队尾
*/

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "doubly_linked_list.h"

/*---------------------------------------实际例题-----------------------------------------*/
//设计一个算法，统计一个带头结点的循环单链表 L所有data域值为 x的节点个数
int count(LinkNode* L, ElemType x)
{
    int i = 0;
    LinkNode* p = L->next;
    while (p != L)  //*循环结束条件为 p != L
    {
        if(p->data == x)
            i++;
        p = p->next;
    }
    return i;
}

//有一个带头结点的循环双链表 L，设计一个算法删除第一个 data域为 x的节点
bool delelem(DLinkNode* &L, ElemType x)
{
    DLinkNode *p = L->next;
    while(p != L && p->data != x)   //查找第一个 data域为 x的元素
        p = p->next;
    if(p != L)
    {
        p->next->prior = p->prior;  //循环双链表的删除元素方法
        p->prior->next = p->next;
        free(p);
        return true;
    }
    else
        return false;
}

//设计一个算法，判断带头结点的循环双链表 L(包含两个以上的元素)中的元素是否对称
bool Symm(DLinkNode *L)
{
    bool flag = true;   //对称标志，初始时为 true
    DLinkNode * p = L->next;
    DLinkNode * q = L->prior;
    while (flag)
    {
        if(p->data != q->data)  //对应节点不对成
            flag =false;
        else
        {
            if(p == q || p == q->prior) break;  //分别为链表长度为奇偶时的终止条件 
            p = p->next;
            q = q->prior;
        }
    }
    return flag;   
}
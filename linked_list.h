/**
 * @file linked_list.h
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    linked_list 单链表

    基础知识：
    头节点 head：通常每个链表都会包含一个头节点，并通过头节点的指针（头指针 head pointer）唯一标识该链表
    首指针 first pointer：指向首节点或者开始节点的指针
    尾指针 tail pointer：指向尾节点的指针
*/

#include <stdlib.h>
#include <stdio.h>
#define ElemType int    //自定数据类型

/*-------------------------------------单链表的定义---------------------------------------*/

typedef struct LNode {
    ElemType data;  //数据域
    struct LNode* next; //存放后继节点
}LinkNode;


/*--------------------------------------创建单链表---------------------------------------*/


/*---------------------------------单链表基本运算的实现------------------------------------*/

/**
 * @file ordered_list.c
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-06-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
    ordered list 有序表：表内元素以递增（递减）方式排列
    有序表元素之间的逻辑关系与线性表完全相同，
    因此可以用顺序表 SqList，单链表 LinkNode，双链表 DLinkNode 进行储存
*/
#include "sequential_list.h"
#include "linked_list.h"
//若以 SqList存储有序表，只有插入操作有所差异，其余都是相同的
void ListInsert(SqList* &L,ElemType e)
{
    int i = 0, j;
    while(i < L->length && L->data[i] < e)  //查找插入 e 的位置
        i++;
    for (j = ListLength(L); j > i; j--) {   //data[i]及后面的元素后移一个位置。
        L->data[j] = L->data[j - 1];    
    }
    L->data[j] = e;
    L->length++;
    
}
//若以 LinkNode存储有序表，只有插入操作有所差异，其余都是相同的
void ListInsert(LinkNode* &L,ElemType e)
{
    LinkNode *pre = L, *s;
    while(pre->next != NULL && pre->next->data < e) //找到插入的前驱节点
        pre = pre->next;
    s = (LinkNode*)malloc(sizeof(LinkNode));
    s->data = e;
    s->next = pre->next;
    pre->next = s;
}

//二路归并算法
//假设有两个有序表 LA 和 LB将它们合并成一个有序表LC(假设不存在重复元素),要求不破坏 LA和 LB
//顺序表
void UnionList(SqList *LA, SqList *LB, SqList* &LC)
{
    int i = 0, j = 0, k = 0;    //i, j分别记录 LA、LB的下标， k为 LC中元素的个数
    LC = (SqList*)malloc(sizeof(SqList));
    while(i < LA->length && j < LB->length) {
        if(LA->data[i] < LB->data[j]) {
            LC->data[k] = LA->data[i];
            i++;
            k++;
        } else {    // LA->data[i] > LB->data[j]
            LC->data[k] = LB->data[j];
            j++;
            k++;
        }
    }
    while(i < LA->length) { //LA尚未扫描完，将剩余元素插入 LC中
        LC->data[k] = LA->data[i];
        i++;
        k++;
    }
    while(j < LB->length) { //LB尚未扫描完，将剩余元素插入 LC中
        LC->data[k] = LB->data[j];
        i++;
        k++;
    }
    LC->length = k;
}

//单链表
void UnionList1(LinkNode *LA, LinkNode *LB, LinkNode *&LC)
{
    LinkNode *pa = LA->next, *pb = LB->next, *r, *s;
    LC = (LinkNode*)malloc(sizeof(LinkNode));   //创建头结点
    r = LC;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = pa->data;
            r->next = s;
            r = s;
            pa = pa->next;
        } else {    // LA->data[i] > LB->data[j]
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = pb->data;
            r->next = s;
            r = s;
            pb = pb->next;
        }
        while (pa != NULL) {    //LA尚未扫描完，将剩余元素插入 LC中
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = pa->data;
            r->next = s;
            r = s;
            pa = pa->next;
        }
        while (pb != NULL) {    //LB尚未扫描完，将剩余元素插入 LC中
            s = (LinkNode*)malloc(sizeof(LinkNode));
            s->data = pb->data;
            r->next = s;
            r = s;
            pb = pb->next;
        }
        
    }
}

//现有 3个带头结点的有序单链表LA、LB和 LC。设计一个算法：将操作后的链表 LA中仅剩下 3个表中均包含的数据元素的节点，并释放无用节点
//时间复杂度为O(m+n+p),m、n、p分别为三个表的长度
void Commode(LinkNode *&LA, LinkNode *LB, LinkNode *LC)
{
    LinkNode* pa = LA->next, *pb = LB->next, *pc = LC->next, *q, *r;
    LA->next = NULL;    //此时 LA作为新建单链表的头结点
    r = LA;     //r 指向 LA的尾指针
    while(pa != NULL) {
        while (pb != NULL && pa ->data > pb->data)  //pa节点与pb节点比较，找到一个pb>=pa的节点
            pb = pb->next;
        while (pc != NULL && pa ->data > pc->data)  //pa节点与pc节点比较，找到一个pc>=pa的节点
            pc = pc->next;
        if (pb != NULL && pc != NULL && pa->data == pb->data && pa->data == pc->data) {
            r->next = pa;   //pa为三者相同的节点，插入LA
            r = pa;
            pa = pa->next;  //下一个节点比较
        } else {    //pa不是符合条件的节点
            q = pa;
            pa = pa->next;  //下一个节点比较，释放pa节点
            free(pa);
        }
    }
    r->next = NULL; //尾插法将 r置空
}

//有一个有序单链表 L，设计一个尽可能高效的算法删除值域重复的节点
void dels(LinkNode *&L)
{
    LinkNode *p = L->next, *q;
    while (p != NULL) {
        if(p->data == p->next->data) {
            q = p->next;    //q保存重复节点
            p->next = q->next;  //删除重复节点
            free(p);
        } else {
            p = p->next;    //不是重复节点，p下移
        }
    }
}

//求两个长度相同的有序表的中位数（两个表所有元素升序排列的中位数）
//二路归并算法延申，只要 k = A|B->length 即为找到中位数
ElemType M_Search(SqList *A, SqList *B)
{
    int i = 0, j = 0, k = 0;    // k记录归并后顺序表的长度，i记录 A的位置，j记录 B的位置
    while (i < A->length && j < B->length) {
        k++;    //归并后长度加 1
        if (A->data[i] < B->data[j]) {  //归并插入元素为 A[i]
            if (k == A->length)
                return A->data[i];
            i++;
        } else {    //A->data[i] > B->data[j]
            if (k == B->length) //归并插入元素为 A[j]
                return B->data[j];
            j++;
        }
    }
}

/**
 * @file BST二叉搜索树.cpp
 * @author Akira
 * @brief 
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
using namespace std;

#define KeyType int
#define InfoType int
typedef struct node{
    KeyType key;
    InfoType data;
    struct node *lchlid, *rchild;
}BSTnode;

//BST的插入
bool InsertBST(BSTnode *&bt, KeyType k)
//在二叉搜索树 bt中插入一个关键字为 k的节点
{
    if (bt == NULL)                      //原树为空
    {
        bt = (BSTnode*)malloc(sizeof(BSTnode));
        bt->key = k; bt->lchlid = bt->rchild = NULL;
    }
    else if (k == bt->key)              //树中存在相同关键字的节点，返回false
        return false;
    else if (k < bt->key)
        return InsertBST(bt->lchlid, k);    //插入左子树
    else
        return InsertBST(bt->rchild, k);    //插入右子树
}

//生成BST
BSTnode* CreateBST(KeyType a[], int n)
//返回 BST树根节点的指针
{
    BSTnode *bt = NULL; //初始 bt为空树
    int i = 0;
    while (i < n)
    {
        InsertBST(bt, a[i]);
        i++;
    }
    return bt;
}

//BST 的查找
BSTnode *SearchBST(BSTnode *bt, KeyType k)
{
    if(bt == NULL || bt->key == k)          //递归条件结束
        return bt;
    if(k < bt->key)
        return SearchBST(bt->lchlid, k);    //在左子树中递归查找
    else
        return SearchBST(bt->rchild, k);    //在右子树中递归查找
}

//BST的删除
bool DeleteBST(BSTnode *&bt, KeyType k)
{
    if (bt == NULL)
        return false;
    else
    {
        if (k < bt->key)
            return DeleteBST(bt->lchlid, k);
        else if (k > bt->key)
            return DeleteBST(bt->rchild , k);
        else
        {
            Delete(bt);
            return true;
        }
    }
}
void Delete(BSTnode *& p)
{
    BSTnode *q;
    if (p->rchild == NULL)
    {
        q = p;
        p = p->lchlid;
        free(q);
    }
    else if (p->lchlid == NULL)
    {
        q = p;
        p = p->rchild;
        free(q);
    }
    else Deletel(p,p->lchlid);  //左右子树都存在的情况
}
void Deletel(BSTnode *p, BSTnode *&r)   //r指向p的左孩子
{
    BSTnode *q;
    if(r->rchild != NULL)   //递归找节点 r的最右下节点
        Deletel(p, r->rchild);
    else                    //找到了最右下节点 r
    {
        p->key = r->key;
        p->data = r->data;  //将节点 p用节点 r替代
        q = r;
        r = r->lchlid;      //同节点 r的右孩子接替它
        free(q);
    }
}
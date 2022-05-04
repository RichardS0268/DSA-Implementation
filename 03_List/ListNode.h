#ifndef __LISTNODE__
#define __LISTNODE__

template <typename T> 
struct ListNode
{
    T data; //数值
    ListNode<T>* pred;
    ListNode<T>* succ;
    ListNode() {} //针对header和trailer的构造
    ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL): data(e), pred(p), succ(s) {}; // 默认构造器
    ListNode<T>* insertAsPred(T const & e); //前插入
    ListNode<T>* insertAsSucc(T const & e); //后插入
};

template <typename T>  
using ListNodePosi = ListNode<T>*;

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const & e){//O(1)的时间，但new操作耗时
    ListNodePosi<T> x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x; // 建立链接，返回新节点的位置
} //得益于哨兵，即便this是首节点也不用特殊处理

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const &e){ //与insertAsPred完全对称
    ListNodePosi<T> x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
} 

#endif


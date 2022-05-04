#ifndef __QUADLISTNODE__
#define __QUADLISTNODE__

#include "./Entry.h"
#include <iostream>
using namespace std;

template <typename T> struct QuadlistNode;
template <typename T> using QListNodePosi = QuadlistNode<T>*; // 跳转表节点位置
template <typename T> struct QuadlistNode { // QuadlistNode模板类
   T entry; // 所存词条
   QListNodePosi<T> pred; // 前驱
   QListNodePosi<T> succ; // 后继
   QListNodePosi<T> above; // 上邻
   QListNodePosi<T> below; // 下邻

   // 构造器, 分别指定其四个邻居
   QuadlistNode (T e = T(), QListNodePosi<T> p = NULL, QListNodePosi<T> s = NULL, QListNodePosi<T> a = NULL, QListNodePosi<T> b = NULL ): entry ( e ), pred ( p ), succ ( s ), above ( a ), below ( b ) {}

    // 插入新节点，以当前节点为前驱，以节点b为下邻
   QListNodePosi<T> insertAsSuccAbove ( T const& e, QListNodePosi<T> b = NULL );
};

// 将e作为当前节点的后继、b的上邻插入Quadlist
template <typename T> 
QListNodePosi<T> QuadlistNode<T>::insertAsSuccAbove ( T const& e, QListNodePosi<T> b ) { 
   QListNodePosi<T> x = new QuadlistNode<T> ( e, this, succ, NULL, b ); // 创建新节点
   succ->pred = x; succ = x; // 设置水平逆向链接
   if (b) b->above = x; // 设置垂直逆向链接(如果b非空)
   return x; // 返回新节点的位置
}

#endif
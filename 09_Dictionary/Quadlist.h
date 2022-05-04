#ifndef __Quadlist__
#define __Quadlist__
#include "QuadlistNode.h" // 引入Quadlist节点类

template <typename T> 
class Quadlist { // Quadlist（四联表）模板类
private:
   int _size; QListNodePosi<T> header, trailer; // 规模、头哨兵、尾哨兵
protected:
   void init(); // Quadlist创建时的初始化
   int clear(); // 清除所有节点
public:
// 构造函数
   Quadlist() { init(); } // 默认
// 析构函数
   ~Quadlist() { clear(); delete header; delete trailer; } // 删除所有节点，释放哨兵
// 只读访问接口
   int size() const { return _size; } // 规模
   bool empty() const { return _size <= 0; } // 判空
   QListNodePosi<T> first() const { return header->succ; } // 首节点位置
   QListNodePosi<T> last() const { return trailer->pred; } // 末节点位置
   bool valid ( QListNodePosi<T> p ) // 判断位置p是否对外合法
   { return p && ( trailer != p ) && ( header != p ); } 
// 可写访问接口
   T remove ( QListNodePosi<T> p ); // 删除（合法）位置p处的节点，返回被删除节点的数值
   // 将*e作为p的后继、b的上邻插入
   QListNodePosi<T> insertAfterAbove ( T const& e, QListNodePosi<T> p, QListNodePosi<T> b = NULL ); 
// 遍历
   void traverse ( void (* ) ( T& ) ); // 遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
   template <typename VST> // 操作器
   void traverse ( VST& ); // 遍历各节点，依次实施指定操作（函数对象，可全局性修改节点）
}; // Quadlist


template <typename T> // Quadlist初始化，创建Quadlist对象时统一调用
void Quadlist<T>::init() { 
   header = new QuadlistNode<T>; // 创建头哨兵节点
   trailer = new QuadlistNode<T>; // 创建尾哨兵节点
   header->succ = trailer; header->pred = NULL; // 沿横向联接哨兵
   trailer->pred = header; trailer->succ = NULL; // 沿横向联接哨兵
   header->above = trailer->above = NULL; // 纵向的后继置空
   header->below = trailer->below = NULL; // 纵向的前驱置空
   _size = 0; // 记录规模
} // 如此构造的四联表，不含任何实质的节点，且暂时与其它四联表相互独立


template <typename T> // 将e作为p的后继、b的上邻插入Quadlist
QListNodePosi<T> Quadlist<T>::insertAfterAbove( T const& e, QListNodePosi<T> p, QListNodePosi<T> b )
{ _size++; return p->insertAsSuccAbove ( e, b );} // 返回新节点位置（below = NULL）


template <typename T> // 删除Quadlist内位置p处的节点，返回其中存放的词条
T Quadlist<T>::remove ( QListNodePosi<T> p ) { // assert: p为Quadlist中的合法位置
   p->pred->succ = p->succ; p->succ->pred = p->pred; _size--;// 摘除节点
   T e = p->entry; delete p; // 备份词条，释放节点
   return e; // 返回词条
}

template <typename T> int Quadlist<T>::clear() { // 清空Quadlist
   int oldSize = _size;
   while ( 0 < _size ) remove ( header->succ ); // 循环调用remove函数，逐个删除所有节点
   return oldSize;
}


template <typename T> //遍历Quadlist，对各节点依次实施visit操作
void Quadlist<T>::traverse ( void ( *visit ) ( T& ) ) { //利用函数指针机制，只读或局部性修改
   QListNodePosi<T> p = header;
   while ( ( p = p->succ ) != trailer ) visit ( p->data );
}


template <typename T> template <typename VST> //遍历Quadlist，对各节点依次实施visit操作
void Quadlist<T>::traverse ( VST& visit ) { //利用函数对象机制，可全局性修改
   QListNodePosi<T> p = header;
   while ( ( p = p->succ ) != trailer ) visit ( p->data );
}

#endif
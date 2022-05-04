#ifndef __VECTORUTIL__
#define __VECTORUTIL__

#include "../00_util/utils.h"
#include "Vector.h"
#include <cstdlib>
#include <ctime> //通常用当前时刻设置随机种子
#include <iostream>
using namespace std;

template <typename T> void checkOrder ( Vector<T> & V ) { //判断向量是否整体有序
   int unsorted = 0; //逆序计数器
   struct CheckOrder<T> A(unsorted, V[0]);
   V.traverse (A); //进行遍历
   if ( 0 < unsorted )
      printf ( "Unsorted with %d adjacent inversion(s)\n", unsorted );
   else
      printf ( "Sorted\n" );
}

template <typename T> void crc ( Vector<T> & V ) { //统计向量的特征（所有元素之和）
   T crc = 0; 
   struct Crc<T> A(crc);
   V.traverse (A); //以crc为基本操作进行遍历
   printf ( "CRC =" ); print ( crc ); printf ( "\n" ); //输出统计得到的特征
}

template <typename T> void decrease ( Vector<T> & V ) //统一递减向量中的各元素
{  struct Decrease<T> A;
   V.traverse (A);  } //以Decrease<T>()为基本操作进行遍历

template <typename T> void _double ( Vector<T> & V ) //统一加倍向量中的各元素
{  struct Double<T> A;
   V.traverse (A);  } //以Double<T>()为基本操作进行遍历

template <typename T> void increase ( Vector<T> & V ) //统一递增向量中的各元素
{  struct Increase<T> A;
   V.traverse (A);  } //以Increase<T>()为基本操作进行遍历

#endif
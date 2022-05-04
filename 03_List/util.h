#ifndef __UTIL__
#define __UTIL__

#include "../00_util/utils.h"
#include "List.h"
#include <iostream>
using namespace std;

template <typename T> void checkOrder ( List<T> & L ) { //判断列表是否整体有序
   int nInv = 0; //逆序计数器
   struct CheckOrder<T> A(nInv, L.first()->data);
   L.traverse (A); //进行遍历
   if ( 0 < nInv )
      printf ( "Unsorted with %d adjacent inversion(s)\n", nInv );
   else
      printf ( "Sorted\n" );
}


template <typename T> void crc ( List<T> & L ) { //统计列表的特征（所有元素总和）
    T crc = 0; 
    struct Crc<T> A(crc);
    L.traverse (A); //以crc为基本操作进行遍历
    printf ( "CRC =" ); 
    print ( crc ); 
    printf ( "\n" ); //输出统计得到的特征
}


template <typename T> void decrease ( List<T> & L ) //统一递减列表中的各元素
{  
    struct Decrease<T> A;
    L.traverse (A);  
} //以Decrease<T>()为基本操作进行遍历


template <typename T> void half ( List<T> & L ) //统一减半列表中的各元素
{  
    struct Half<T> A;
    L.traverse (A);  
} //以Half<T>()为基本操作进行遍历

template <typename T> void increase ( List<T> & L ) //统一递增列表中的各元素
{  
    struct Increase<T> A;
    L.traverse (A);  
} //以Increase<T>()为基本操作进行遍历


#endif
#include "Vector.h"
#include <iostream>
using namespace std;

template<class T>
void Vector<T>::copyFrom(T const * A, int lo, int hi){
    _elem = new T[_capacity = max(DEFAULT_CAPACITY, 2*(hi-lo))];
    for (_size = 0; lo < hi; _size++, lo++){
        _elem[_size] = A[lo];
    } //O(hi - lo) = O(n)
}

template<class T>
void Vector<T>::expand(){
    if (_size < _capacity) return; //尚未满员时不用扩容
    _capacity = max(_capacity, DEFAULT_CAPACITY);
    T* oldElem = _elem; //初始化一个新的 指针
    _elem = new T[_capacity <<= 1]; // 容量加倍
    for (int i = 0; i < _size; i++){
        _elem[i] = oldElem[i]; //T为基本类型，或已重载复制操作符“=”
    }
    delete[] oldElem;//释放原空间
} //虽然容量加倍后数据区的物理地址改变，但不会出现野指针

template<class T>
void Vector<T>::shrink(){
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return; //25%为界限
    T* oldElem = _elem; 
    _elem = new T[_capacity >>= 1] // 容量减半
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制内容
    delete [] oldElem;
}

template<class T>
T & Vector<T>::operator[](int r){return _elem[r];}

template<class T>
const T & Vector<T>::operator[](int r) const{return _elem[r];}

template<class T>
int Vector<T>::insert(int r, T const & e){
    expand();
    for (int i = _size; r > i; i--){ // O(n-r):自后向前
        _elem[i] = _elem[i-1]; //后继元素顺次后移一个单位
    }
    _elem[r] = e;
    _size++;
    return r; //返回索引
}

template <class T>
int Vector<T>::remove(int lo, int hi){ //lo,hi合法
    if (lo == hi) return 0;//退化情况
    while (hi < _size){
        _elem[lo++] = _elem[hi++]; // O(n-hi):[hi,n)顺次前移
    }
    _size = lo;
    shrink();//如有必要进行缩容
    return hi - lo; //返回被删除元素的数目
}

template <class T> 
T Vector<T>::remove(int r){
    T e = _elem[r];
    remove(r, r+1);
    return e;//返回被删除元素
} //O(n-r)

template <class T>
int Vector<T>::uniquify() {
    int i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink(); //直接截去尾部多余元素
    return j - i;
} //高效算法O(n)
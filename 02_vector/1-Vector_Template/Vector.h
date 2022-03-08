#ifndef __VECTOR__
#define __VECTOR__
#define DEFAULT_CAPACITY 5

template <typename T> 
class Vector {
private: 
    int _size; int _capacity; T* _elem;

protected:

public:
    //=====构造与析构====
    //默认
    Vector(int cap = DEFAULT_CAPACITY){
        _elem = new T[_capacity = cap]; 
        _size = 0
    }
    //数组区间复制
    Vector(T const * A, int lo, int hi){
        copyFrom(A, lo, hi);
    }
    //向量区间复制
    Vector(Vector<T> const & V, int lo, int hi){
        copyFrom(V._elem, lo, hi);
    }
    //向量整体复制
    Vector(Vector<T> const & V){
        copyFrom(V._elem, 0, V._size);
    }
    //析构函数
    ~Vector(){delete [] _elem;}

    //========基本操作========
    //复制函数
    void copyFrom(T const* A, int lo, int hi);
    //扩容函数-加倍扩容
    void expand();
    //缩容
    void shrink();
    //重载下标操作符‘[]’
    T & operator[](int r);//可作为左值：V[r]=(T)(2*X+3)
    const T & operator[](int r) const; //仅限于右值：T x = V[r] + U[s]*W[t]
    //插入
    int insert(int r, T const & e);
    //区间删除
    int remove(int lo, int hi);
    //单元素删除
    T remove(int r);
    //唯一化
    int uniquify();

    //=======排序=========
    void bubbleSort(int lo, int hi); //冒泡排序
    void selectionSort(int lo, int hi); //选择排序
    void mergeSort(int lo, int hi); //归并排序
    void heapSort(int lo, int hi); //堆排序
    void quickSort(int lo, int hi); //快速排序
    void shellSort(int lo, int hi); //希尔排序

};

#endif
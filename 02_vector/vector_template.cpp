#define Rank int
#define DEFAULT_CAPACITY 5

template <typename T> 
class my_Vector {
private: 
    Rank _size; Rank _capacity; T* _elem;

protected:

public:
    //=====构造与析构====
    //默认
    Vector(int cap = DEFAULT_CAPACITY){
        _elem = new T[_capacity = cap]; 
        _size = 0
    }
    //数组区间复制
    Vector(T const * A, Rank lo, Rank hi){
        copyFrom(A, lo, hi);
    }
    //向量区间复制
    Vector(Vector<T> const & V, Rank lo, Rank hi){
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
    void copyFrom(T const* A, Rank lo, Rank hi);
    //扩容函数-加倍扩容
    void expand();
    //缩容
    void shrink();
    //重载下标操作符‘[]’
    T & operator[](Rank r);//可作为左值：V[r]=(T)(2*X+3)
    const T & operator[](Rank r) const; //仅限于右值：T x = V[r] + U[s]*W[t]
    //插入
    Rank insert(Rank r, const & e);
    //区间删除
    int remove(Rank lo, Rank hi);
    //单元素删除
    T remove(Rank r);
    //唯一化
    int uniquify();

    //=======排序=========
    void bubbleSort(Rank lo, Rank hi); //冒泡排序
    void selectionSort(Rank lo, Rank hi); //选择排序
    void mergeSort(Rank lo, Rank hi); //归并排序
    void heapSort(Rank lo, Rank hi); //堆排序
    void quickSort(Rank lo, Rank hi); //快速排序
    void shellSort(Rank lo, Rank hi); //希尔排序

};


template<class T>
void my_Vector<T>::copyFrom(T const * A, Rank lo, Rank hi){
    _elem = new T[_capacity = max(DEFAULT_CAPACITY, 2*(hi-lo))];
    for (_size = 0; lo < hi; _size++, lo++){
        _elem[_size] = A[lo];
    } //O(hi - lo) = O(n)
}

template<class T>
void my_Vector<T>::expand(){
    if (_size < _capacity) return; //尚未满员时不用扩容
    _capacity = max(_capacity, DEFAULT_CAPACITY);
    T* oldElem = _elem; //初始化一个新的 指针
    _elem = new T[_capacity <<= 1]; // 容量加倍
    for (Rank i = 0; i < _size; i++){
        _elem[i] = oldElem[i]; //T为基本类型，或已重载复制操作符“=”
    }
    delete[] oldElem;//释放原空间
} //虽然容量加倍后数据区的物理地址改变，但不会出现野指针

template<class T>
void my_Vector<T>::shrink(){
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return; //25%为界限
    T* oldElem = _elem; 
    _elem = new T[_capacity >>= 1] // 容量减半
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制内容
    delete [] oldElem;
}

template<class T>//要求rank合法
T & my_Vector<T>::operator[](Rank r){return _elem[r];}

template<class T>//要求rank合法
const T & my_Vector<T>::operator[](Rank r) const{return _elem[r];}

template<class T>
Rank my_Vector<T>::insert(Rank r, T const & e){
    expand();
    for (Rank i = _size; r > i; i--){ // O(n-r):自后向前
        _elem[i] = _elem[i-1]; //后继元素顺次后移一个单位
    }
    _elem[r] = e;
    _size++;
    return r; //返回索引
}

template <class T>
int my_Vector<T>::remove(Rank lo, Rank hi){ //lo,hi合法
    if (lo == hi) return 0;//退化情况
    while (hi < _size){
        _elem[lo++] = _elem[hi++]; // O(n-hi):[hi,n)顺次前移
    }
    _size = lo;
    shrink();//如有必要进行缩容
    return hi - lo; //返回被删除元素的数目
}

template <class T> 
T my_Vector<T>::remove(Rank r){
    T e = _elem[r];
    remove(r, r+1);
    return e;//返回被删除元素
} //O(n-r)

template <class T>
int my_Vector<T>::uniquify() {
    Rank i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink(); //直接截去尾部多余元素
    return j - i;
} //高效算法O(n)

//============有序向量-查找算法===========
//Bin_A -> Bin_B -> Bin_C
//注意hi是最高位索引，不要越界
template <typename T> 
static Rank binSearch(T* S, T const & e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        e < S[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1; //查找失败
} // O(logn)

//插值查找
template <typename T>
static Rank insertSearch(T* S, T const & e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mid = lo + (hi - lo)(e - S[lo])/(S[hi]-S[lo]);
        e < S[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1;
} // O(loglogn)

//=============排序算法==============
template <typename T>
void my_Vector<T>::bubbleSort(Rank lo, Rank hi){ //冒泡排序
    while (lo < --hi){ //逐趟起泡排序
        for (Rank i = lo; i < hi; i++){ //若相邻元素 
            if (_elem[i] > _elem[i+1]) //逆序
                swap(_elem[i], _elem[i+1]) //则交换顺序
        }
    }
}

template <typename T>
void my_Vector<T>::selectionSort(Rank lo, Rank hi){ //选择排序

}

template <typename T>
void my_Vector<T>::mergeSort(Rank lo, Rank hi){ //归并排序

}

template <typename T>
void my_Vector<T>::heapSort(Rank lo, Rank hi){ //堆排序

}

template <typename T>
void my_Vector<T>::quickSort(Rank lo, Rank hi){ //快速排序

}

template <typename T>
void my_Vector<T>::shellSort(Rank lo, Rank hi){ //希尔排序

}
#include <iostream>
using namespace std;


template<typename T>
void merge(T* _elem, int lo, int mi, int hi);

template <typename T> 
void mergeSort(T* _elem, int lo, int hi){
    if (hi - lo < 2) return; //递归基
    int mi = (lo + hi) >> 1; //以中点为界左右分别排序
    mergeSort(_elem, lo, mi);
    mergeSort(_elem, mi, hi);
    merge(_elem, lo, mi, hi); //归并
}

template<typename T>
void merge(T* _elem, int lo, int mi, int hi){
    int i = 0;
    T* A = _elem + lo; //A = _elem[lo, hi],就地，未重新开辟区间
    int j = 0, lb = mi - lo;
    T* B = new T[lb];
    for (int i = 0; i < lb; i++){
        B[i] = A[i];
    }
    int k = 0, lc = hi - mi;
    T* C = _elem + mi; //C = _elem[mi, hi],就地，未重新开辟区间
    while ((j < lb) && (k < lc)) //反复比较B,C的首元素
        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    while (j < lb) // 若C先耗尽
        A[i++] = B[j++]; //将B中残余后缀加到A中
    delete [] B;  
}

int main(){
    int A[13] = {2, 4, 5, 1, 6, 7, 9, 11, 13, 15, 1, 4, 6};
    mergeSort<int>(A, 0, 13);
     for (int i = 0; i < 13; i++){
        cout << A[i] << " " ;
    }
    cout << endl;
    return 0;
}
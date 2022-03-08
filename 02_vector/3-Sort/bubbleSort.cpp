#include <iostream>
using namespace std;

template <typename T> 
void bubbleSort1(T* _elem, int lo, int hi){
    while (lo < --hi){ //从后往前，逐趟扫描
        for (int i = lo; i < hi; i++){ //若相邻元素
            if (_elem[i] > _elem[i+1]) //逆序
                swap(_elem[i], _elem[i+1]); //则交换
        }
    }
}

template <typename T> 
void bubbleSort2(T* _elem, int lo, int hi){ //可以提前终止
    for (bool sorted = false; sorted = !sorted; ) {
        for (int i = lo; i < hi-1; i++){
            if(_elem[i] > _elem[i+1]){
                swap(_elem[i], _elem[i+1]);
                sorted = false; //仍未完全有序
            }
        } //else ... 提前终止
    }
}

template <typename T> 
void bubbleSort3(T* _elem, int lo, int hi){
    for (int last = --hi; lo < hi; hi = last){
        for (int i = last = lo; i < hi; i++){
            if(_elem[i] > _elem[i+1]){
                swap(_elem[i], _elem[i+1]);
                last = i; //逆序对只可能残留于[lo, last)
            }
        }
    }
}

int main(){
    int A1[13] = {2, 4, 5, 1, 6, 7, 9, 11, 13, 15, 1, 4, 6};
    int A2[13] = {2, 4, 5, 1, 6, 7, 9, 11, 13, 15, 1, 4, 6};
    int A3[13] = {2, 4, 5, 1, 6, 7, 9, 11, 13, 15, 1, 4, 6};
    bubbleSort1<int>(A1, 0, 13);
    bubbleSort2<int>(A2, 0, 13);
    bubbleSort3<int>(A3, 0, 13);
    cout << "bubbleSort1: " << endl;
    for (int i = 0; i < 13; i++){
        cout << A1[i] << " " ;
    }
    cout << endl;

    cout << "bubbleSort2: " << endl;
    for (int i = 0; i < 13; i++){
        cout << A2[i] << " " ;
    }
    cout << endl;

    cout << "bubbleSort3: " << endl;
    for (int i = 0; i < 13; i++){
        cout << A3[i] << " " ;
    }
    cout << endl;
    return 0;
}
#include "Vector.h"
#include <iostream>
#include "Vector.h"
using namespace std;

template <typename T> struct Increase{
    virtual void operator() (T& e) {e++;};
};

template <typename T> struct Show{
    virtual void operator() (T& e) {cout << e << " ";};
};

template<typename T> void increase(Vector<T> & V){
    struct Increase<int> A;
    V.traverse(A);
    struct Show<int> B;
    V.traverse(B);
}

int main(){
    int A[5] = {1, 2, 3, 4, 5};
    Vector<int> B(A, 5);
    increase<int>(B);
    return 0;
}
#ifndef __STACK_H__
#define __STACK_H__
#include "../02_vector/Vector.h"
#include <iostream>
using namespace std;

template<typename T>
class Stack :public Vector<T>{
public:
    void push(T const& e){this->insert(e);} //入栈
    T pop() {return this->remove(this->size() - 1);} //出栈
    T & top() {return (*this)[this->size() - 1];} //取顶
};

#endif
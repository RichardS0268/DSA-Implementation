#ifndef __LIST_H__
#define __LIST_H__

#include "../03_list/List.h" // 以List为基类
using namespace std;

template <typename T> class Queue: public List<T> {
public:
    void enqueue(T const & e) {
        this->insertAsLast(e);
    } //入队：尾部插入
    T dequeue() {
        return this->remove(this->first()); //出队：首部删除
    }
    T& front() {
        return this->first()->data; //返回队首
    }
};

#endif
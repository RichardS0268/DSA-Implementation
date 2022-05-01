#include <assert.h>
#include <iostream>
#include <cstring>
using namespace std;
#define DEFAULT_CAPACITY  5 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class CursorList { //游标式列表
protected:
    int _size; int _capacity; //规模、容量
    int* _link; T* _elem; //游标指针、数据区
    int _data, _free; //数据链表和空闲链表的起点
public:
    CursorList ( int c = DEFAULT_CAPACITY ) { //容量为c
    //初始化时即开辟出足够空间，消除后续再new的时间开销
        _link = new int[_capacity = c]; //游标指针向量
        _elem = new T[_capacity = c]; 
        memset ( _elem, 0, c * sizeof ( T ) ); //数据向量
        _data = -1; _size = 0; //数据链表初始为空
        _free = 0; //空闲链表由所有单元依次串接而成
        for ( int i = 0; i < c - 1; i++ ) _link[i] = i + 1;
        _link[c - 1] = -1;
    }
    ~CursorList() { delete [] _link; delete [] _elem; } //释放内部空间
    int size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    int find ( T const& e ) const { //查找
        int i = _data; //从数据链表起点出发
        while ( ( 0 <= i ) && ( e != _elem[i] ) ) i = _link[i]; //依次比对
        return i;
    }
    // 此结构只能实现insert at last ?
    int insert ( T const& e) { //在秩为rank处插入元素e 
        assert ( 0 <= _free );
        int k = _free; //_free指向可以插入的位置
        _free = _link[k]; 
        _elem[k] = e;
        _link[k] = _data; 
        _data = k; //_data指向刚刚插入元素的位置
        _size++; 
        return k;
    }
    int remove ( int k ) { //删除秩为k的元素
        assert ( 0 <= k ); //此前经查找并确认k合法
        if ( _data == k ) //若[k]为首节点
            _data = _link[k];
        else { //否则
            int i = _data; 
            while ( k != _link[i] ) i = _link[i];
            _link[i] = _link[k];
        }
        _link[k] = _free; _free = k; _elem[k] = 0;
        _size--; 
        return k;
    }
    void print() {
        printf ( "size = %d _free = %d _data = %d\n", _size, _free, _data );
        printf("_link: ");
        for ( int i = 0; i < _capacity; i++ ) cout << _link[i] << " "; 
        printf ( "\n" );
        printf("Elements: ");
        for ( int i = 0; i < _capacity; i++ ) cout << _elem[i] << " ";
        // printf ( "\n" );
        // printf("Elements: ");
        // for ( int i = _data; 0 <= i; i = _link[i] ) cout <<  _elem[i] << " ";
        printf ( "\n\n" );
    }
};
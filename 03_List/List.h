#ifndef __LIST__
#define __LIST__
#include <iostream>
#include "ListNode.h"
using namespace std;

template<typename T>
class List{ //列表模板类
private: 
    int _size;
    ListNodePosi<T> header;
    ListNodePosi<T> trailer;

protected:
    void init(); //列表创建时的初始化
    int clear(); //清除所有结点
    void copyNodes(ListNodePosi<T>, int);
    void merge(ListNodePosi<T>&, int, List<T>&, ListNodePosi<T>, int); //归并
    void mergeSort(ListNodePosi<T>&, int); //对从p开始连续的n个节点归并排序
    void selectionSort(ListNodePosi<T>, int); //从对p开始连续的n个节点选择排序
    void insertSort(ListNodePosi<T>, int); //从对p开始连续的n个节点插入排序

public:
// 构造函数
    List() {init();};
    List (List<T> const& L); //整体复制列表L
    List (List<T> const& L, int r, int n); // 复制列表L中r到n项
    List (ListNodePosi<T> p, int n); // 复制列表中自p开始的n项
//析构函数
    ~List(); //释放（包含头尾哨兵在内）的所有节点
//只读访问接口
    int size() const {return _size;}
    bool empty() const {return _size <= 0;}
    T& operator[] (int r) const; //重载，支持寻秩访问，O(r)，效率低
    ListNodePosi<T> first() const {return header->succ;} //首节点位置
    ListNodePosi<T> last() const {return trailer->pred;} //末节点位置
    bool valid (ListNodePosi<T> p){ //判断位置p对外是否合法
        return p && (trailer != p) && (header != p); //头尾哨兵不对外开放 
    }
    int disordered() const; // 判断列表是否已经排序
    ListNodePosi<T> find(T const& e) const{ //无序列表查找
        return find(e, _size, trailer);
    }
    ListNodePosi<T> find(T const& e, int n, ListNodePosi<T> p) const; //无序区间查找
    ListNodePosi<T> search(T const& e) const{ //有序列表查找
        return search(e, _size, trailer);
    }
    ListNodePosi<T> search(T const& e, int n, ListNodePosi<T> p) const; //有序区间查找
    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //在p及其n-1个后继中选出最大者
    ListNodePosi<T> selectMax(){return selectMax(header->succ, _size);} //整体最大者
//可写访问接口
    ListNodePosi<T> insertAsFirst (T const& e){ //将e当做首节点插入
        _size++;
        return header->insertAsSucc(e);
    }
    ListNodePosi<T> insertAsLast (T const& e){ //将e当做末节点插入
        _size++;
        return trailer->insertAsPred(e);
    }
    ListNodePosi<T> insert (ListNodePosi<T> p, T const& e){ //将e当做p的后继插入
        _size++;
        return p->insertAsSucc(e);
    }
    ListNodePosi<T> insert (T const& e, ListNodePosi<T> p){ //将e当做p的前驱插入
        _size++;
        return p->insertAsPred(e);
    }
    T remove (ListNodePosi<T> p); //删除合法位置p处的节点，返回被删除节点
    void merge(List<T>& L) {
        ListNodePosi<T> A = first();
        merge(A, size(), L, L.first(), L.size());
    }
    void sort (ListNodePosi<T> p, int n, int type = 1); //列表区间排序
    void sort() {sort(first(), _size, 1);} //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置
//遍历
    void traverse(void(* ) (T& )); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template <typename VST> //操作器
    void traverse(VST &); //遍历，依次实施visit操作（函数对象，课全局性修改）
};


// ==== prtected函数，内部方法 ====
template<typename T>
void List<T>::copyNodes (ListNodePosi<T> p, int n){ //O(n)
    init(); //创建头，尾哨兵
    while (n--){
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
int List<T>::clear(){ //清空列表 O(n)
    int oldSize = _size;
    while (0 < _size) remove(header->succ);
    return oldSize;
}


// ==== public函数 ====
//---- 构造函数，析构函数 ----
template<typename T> //整体复制L
List<T>::List (List<T> const& L){
    copyNodes(L.first(), L._size);
}

template<typename T> //r+n<=L.size()
List<T>::List (List<T> const& L, int r, int n){
    ListNodePosi<T> p = L.first();
    while (0 < r--) p = p->succ;
    copyNodes(p, n);
}

template<typename T>
List<T>::List (ListNodePosi<T> p, int n){ //p为合法节点，其后至少有n-1个合法节点
    copyNodes(p, n);
}

template<typename T>
List<T>::~List(){ //清空列表，释放头尾哨兵,O(n)
    clear();
    delete header;
    delete trailer;
} 

//---- 只读访问接口 ----
template <typename T> 
void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <typename T> 
T& List<T>::operator[](int r) const{ //O(r)，不宜常用
    ListNodePosi<T> p = first();
    while(0 < r--) p = p->succ;
    return p->data;
}

template<typename T> //在无序列表内节点p的n个前驱中(查找对象不包括p本身)，找到等于e的最后者
ListNodePosi<T> List<T>::find(T const& e, int n, ListNodePosi<T> p) const{ //O(n)
    while (0 < n--){
        if ((e == (p = p->pred)->data) && p!=header) return p;
    }
    return NULL; //p越出左边界意味着区间内不含e，查找失败，则返回NULL
}

template<typename T> //在有序列表内节点p的n个前驱中，找到不大于e的最后者
ListNodePosi<T> List<T>::search(T const& e, int n, ListNodePosi<T> p) const{ //O(n)
    while (0 <= n--)
        if (((p = p->pred)->data) <= e) break;
    return p; //返回查找终止的位置
} //失败时，返回左边界的前驱（header），可通过调用valid来判断是否查找成功，无论是否成功，返回位置都可用于插入删除等操作

template <typename T> //排序器统一入口，根据type指定排序算法
void List<T>::sort(ListNodePosi<T> p, int n, int type){ //列表区间排序
    switch (type) {
        case 1: insertSort(p, n); break; //插入排序
        case 2: selectionSort(p, n); break; //选择排序
        default: mergeSort(p, n); break; //归并排序
    }
}

template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n){ //O(n)，一趟扫描
    ListNodePosi<T> max = p;
    for (ListNodePosi<T> cur = p; 1 < n; n--){//后续节点（n个）依次与max->data比较
        if(((cur = cur->succ)->data >= max->data))
            max = cur;
    }
    return max;
}

template <typename T> 
void List<T>::selectionSort(ListNodePosi<T> p, int n){ //选择排序，O(n^2)
    ListNodePosi<T> head = p->pred, tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ; //头尾插桩
    while (1 < n){
        ListNodePosi<T> max = selectMax(head->succ, n);
        insert(remove(max), tail); //insert(ListNodePosi, ListNode) -> 
        tail = tail->pred;
        n--;
    }
}

template <typename T> 
//input sensitive: Best case O(n), worst case O(n^2)
void List<T>::insertSort(ListNodePosi<T> p, int n){ //插入排序
    for (int r = 0; r < n; r++){
        insert(search(p->data, r, p), p->data);//查找（p之前的r个元素中不大于p的最后一个节点）+（将p的值作为后继）插入到该节点之后
        p = p->succ;
        remove(p->pred); //转向下一节点
    }
}

template<typename T>
void List<T>::merge(ListNodePosi<T>& p, int n, List<T>& L, ListNodePosi<T> q, int m){ //O(n+m)
    ListNodePosi<T> pp = p->pred; //归并后p或不再指向首节点，因此需要先记忆，以便返回时更新
    while((0 < m) && (q!=p)){ //从前往后merge，q == p的极端情况就是两者各自有序，且q严格小于p，前n次操作都是加入p重元素（p = p->succ）
        if ((0 < n) && (p->data <= q->data)){
            p = p->succ;
            n--;
        }
        else{ //倘若p已全部归并完，或者q的值更小，就把q的值插到p之前
            insert(L.remove((q = q->succ)->pred), p);
            m--;
        }
    }
    p = pp->succ;
}

template <typename T> 
void List<T>::mergeSort(ListNodePosi<T>& p, int n){ //归并排序
    if (n < 2) return;
    int m = n >> 1;
    ListNodePosi<T> q = p;
    for (int i = 0; i < m; i++) q = q->succ; //均分列表
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m); //归并
}//排序后，p依然指向归并后区间的（新）起点

//---- 可写访问接口 ----
template<typename T>
T List<T>::remove (ListNodePosi<T> p){ //删除合法节点，返回其数值
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--; //释放节点，更新规模
    return e; //返回备份的数值
}

template<typename T>
int List<T>::deduplicate(){ //剔除无序列表中的重复节点 O(n^2)
    if (_size < 2) return 0;
    int oldSize = _size; //记录原规模
    ListNodePosi<T> p = header; int r = 0; //p从首节点开始
    while (trailer != (p = p->succ)){
        ListNodePosi<T> q = find(p->data, r, p); //在p的r个前驱中寻找
        q ? remove(q) : r++; //若的确存在雷同者，则删除，否则秩加一
    } 
    return oldSize - _size; //返回删除节点数
}

template<typename T>
int List<T>::uniquify(){//成批剔除元素，效率更高，O(n)
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first(); ListNodePosi<T> q;
    while (trailer != (q = p->succ)){
        if (p->data != q->data) p = q;
        else remove(q); //delete操作把q的空间释放掉，但q已经声明，且由于while循环，q也不会称为野指针
    }
    return oldSize - _size; //返回删除元素总数
}

template <typename T> 
void List<T>::reverse() { //前后倒置
   if ( _size < 2 ) return; //平凡情况
   ListNodePosi<T> p; ListNodePosi<T> q;
   for ( p = header, q = p->succ; p != trailer; p = q, q = p->succ )
      p->pred = q; //自前向后，依次颠倒各节点的前驱指针
   trailer->pred = NULL; //单独设置尾节点的前驱指针
   for ( p = header, q = p->pred; p != trailer; p = q, q = p->pred )
      q->succ = p; //自前向后，依次颠倒各节点的后继指针
   header->succ = NULL; //单独设置头节点的后继指针
   swap ( header, trailer ); //头、尾节点互换
}

//---- 遍历 ----
template<typename T>
void List<T>::traverse(void(*visit)(T&)){ //借助函数指针机制遍历
    for(ListNodePosi<T> p = header->succ; p!=trailer;p = p->succ){
        visit(p->data);
    }
}

template<typename T>
template<typename VST> //元素类型、操作器
void List<T>::traverse  (VST & visit){ //借助函数对象机制遍历
    for (ListNodePosi<T> p = header->succ; p!=trailer; p = p->succ){
        visit(p->data);
    }
}

#endif
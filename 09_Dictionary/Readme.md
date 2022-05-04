# Dictionary

### 1. Characters

+ 逻辑上的词典是由一组数据构成的集合，其中各元素都是由关键码 (*key*) 和数据项 (*value*) 合成的词条(entry)

+ 借助关键码 (*key*) 直接查找和访问数据元素 —— *call by value*
+ 与映射 (*map*) 不同，二者虽都是词条的结合，但映射要求不同词条的关键码互异，而词典则允许多个词条拥有相同的关键码。除了静态查找，二者都支持动态更新，统称为符号表 (*symbol table*) 
+ 在作为基本数据单位的词条内部，key和value的地位相同，不必加以区分。在符号表的内部也不需要按照大小次序来组织数据项——即便各数据项之间的确定义有某种次序
+ 抛开大小次序的概念，不再属于*CBA (comparison based algorithms)* 范畴，某些操作可突破CBA式算法的复杂度下界

### 2. Interface

> 词典类数据结构 基本接口

| 接口              | 功能                                                       |
| ----------------- | ---------------------------------------------------------- |
| `get(key)`        | 循关键码访问 (*call by value*), 若无相应词条，则返回`NULL` |
| `put(key, value)` | 插入词条 (key, value)，并报告是否成功                      |
| `remove(key)`     | 若存在以key为关键码的词条，则删除并返回true；否则返回false |

> Entry 基本属性和方法

```c++
template <typename K, typename V> struct Entry { // 词条模板类
   K key; V value; // 关键码、数值
   Entry ( K k = K(), V v = V() ) : key ( k ), value ( v ) {}; // 默认构造函数
   Entry ( Entry<K, V> const& e ) : key ( e.key ), value ( e.value ) {}; // 基于克隆的构造函数
   bool operator< ( Entry<K, V> const& e ) { return key <  e.key; }  // 比较器：小于
   bool operator> ( Entry<K, V> const& e ) { return key >  e.key; }  // 比较器：大于
   bool operator== ( Entry<K, V> const& e ) { return key == e.key; } // 判等器：等于
   bool operator!= ( Entry<K, V> const& e ) { return key != e.key; } // 判等器：不等于
};
```

🎈 两种常用的词典类数据结构有 **Skiplist(跳转表)** 和 **Hashtable(散列表)**

### 3. Skiplist

#### 3.1 Characters

+ 在已有的数据结构中，*有序向量* 便于静态查找，但动态维护成本较高；*有序列表* 便于增量式的动态维护，但只能支持顺序查找。*平衡二叉搜索树* 实现两者的优势互补，实现了查找、插入和删除操作均可在 $O(logn)$ 时间内完成。但这些结构的相关算法往往较为复杂，代码实现和调试的难度较大，其正确性和可维护性也很难保证。跳转表 (*Skiplist*）的引入是为了找到一种简便直观的方式，来完成这一任务

+ 它是一种高效的词典结构，其定义与实现完全基于有序列表，查询和维护操作在平均意义下均只需$O(logn)$时间

  <img src="https://github.com/RichardS0268/DSA-Implementation/blob/master/09_Dictionary/docs/skiplist1.png" width="700px" />




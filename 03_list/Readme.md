# List

### 1. Characters

+ List是一种典型的线性数据结构，其在逻辑上连续，而物理上不连续
+ 相较于Vector而言，List的静态操作费时，如有序向量的查找Search，本质上只能通过sequential search的方式来查找（$O(n)$）
+ 但List的动态操作优，如插入删除，仅需$O(1)$

### 2. Interface

> ListNode APT接口

| 接口              | 功能                                          |
| ----------------- | --------------------------------------------- |
| `data()`          | 当前节点所存数据对象                          |
| `pred()`          | 当前节点前驱节点的位置                        |
| `succ()`          | 当前节点后继节点的位置                        |
| `insertAsPred(e)` | 插入前驱节点，存入被引用对象e，返回新节点位置 |
| `insertAsSucc(e)` | 插入后继节点，存入被引用对象e，返回新节点位置 |

> List APT接口

| 接口                                 | 功能                                                         | 适用对象 |
| ------------------------------------ | ------------------------------------------------------------ | -------- |
| `size()`                             | 报告列表当前的规模（节点总数）                               | 列表     |
| `first()` `last()`                   | 返回首、末节点的位置                                         | 列表     |
| `insertAsFirst(e)` `insertAsLast(e)` | 将e作为首、末节点插入                                        | 列表     |
| `insert(p, e)` `insert(e, p)`        | 将e作为节点p的后继、前驱插入（同名函数重载）                 | 列表     |
| `remove(p)`                          | 删除位置p处的节点，返回其数值                                | 列表     |
| `sort()`                             | 调整各节点位置，使之按非降序排列                             | 列表     |
| `find(e)`                            | 查找目标元素e，失败时返回NULL                                | 列表     |
| `search(e)`                          | 查找目标元素e，返回不大于e且秩最大的节点                     | 有序列表 |
| `selectMax()`                        | 返回列表中数值最大的节点                                     | 列表     |
| `deduplicate()`                      | 剔除重复节点                                                 | 列表     |
| `uniquify()`                         | 剔除重复节点                                                 | 有序列表 |
| `reverse()`                          | 将列表中的节点进行首尾翻转                                   | 列表     |
| `traverse(...)`                      | 遍历并统一处理所有节点，处理方法由参数（函数对象或函数指针）指定 | 列表     |

### 3. Sort

+ SelectionSort:

  + 从后往前，依次有序，每次选出unsorted部分中最大的元素插入sorted部分
  + 外循环需要$O(n)$，若采取遍历方式selectMax需$O(n)$，则总体复杂度为$O(n^2)$，在之后的数据结构中，可将selectMax的复杂度降为$O(logn)$，则selectionSort的复杂度随之降为$O(nlogn)$

<img src="https://media.giphy.com/media/2ATrYdqmEkfDAklIMD/giphy.gif" width="700px" div align="center"/>
<img src="https://media.giphy.com/media/2ATrYdqmEkfDAklIMD/giphy.gif" width = "100" height = "100" div align=right />

+ InsertSort：

  + 从前往后，依次有序，对每“新增”的一个元素，在sorted部分中寻找插入位置并插入
  + Best Case -- $O(n)$，全部有序；Worst Case -- $O(n^2)$，全部逆序
  + InsertSort属于输入敏感性(input sensitive)，其总体复杂度取决于数据中逆序对的个数，事实上，每次交换只能减少一个逆序对，程序运行时间为$O(n+I)$，其中I为逆序对个数

### 4. Cursor List

+ 一些语言没有指针的数据类型，可通过Cursor List实现
+ 创建CurNode，CurNode数组即可作为List使用
+ CurNode包括elem和link
+ 在new时实际未开辟新空间，在delete时实际也未清除空间
+ 即使对于有指针类型的语言，由于new和delete很耗时，但对于数据大小不敏感，因此可通过Cursor List，在开始时开辟一大块空间，供List使用，以避免频繁地new和delete带来巨大的时间开销

### 5. Test

+ 测试List功能:

  ```
  # .../03_list 
  g++ test.cpp -o test 
  ./test
  ```

+ 测试Cursor List功能:

  ```
  # .../03_list/CursorList 
  g++ CurList_test.cpp -o CurList_test 
  ./CurList_test
  
  # .../03_list/CursorList
  g++ CurList_p_test.cpp -o CurList_p_test
  ./CurList_p_test n(n为随机初始化List中元素的个数)
  ```

  

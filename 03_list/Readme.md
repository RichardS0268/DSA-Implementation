# List
### 1. Characters
+ List也是一种典型的线性数据结构，其在逻辑上连续，而非物理上连续
+ 相较于vector而言，List的静态操作费时，如有序向量的查找Search，本质上只能通过sequential search的方式来查找（$O(n)$）
+ 但List的动态操作优，如插入删除，仅需$O(1)$

### 2. Sort
+ SelectionSort:
  + 从后往前，依次有序，每次选出unsorted部分中最大的元素插入sorted部分
  + 外循环需要$O(n)$，若采取遍历方式selectMax需$O(n)$，则总体复杂度为$O(n^2)$，在之后的数据结构中，可将selectMax的复杂度降为$O(logn)$，则selectionSort的复杂度随机降为$O(nlogn)$
+ InsertSort：
  + 从前往后，依次有序，对每“新增”的一个元素，在sorted部分中寻找插入位置并插入
  + Best Case -- $O(n)$，全部有序；Worst Case -- $O(n^2)$，全部逆序
  + InsertSort属于输入敏感性(input sensitive)，其总体复杂度取决于数据中逆序对的个数，事实上，每次交换只能减少一个逆序对，程序运行时间为$O(n+I)$，其中I为逆序对个数
### 3. Cursor List
+ 一些语言没有指针的数据类型，可通过Cursor List实现
+ 创建CurNode，CurNode数组即可作为List使用
+ CurNode包括elem和link
+ 在new时实际未开辟新空间，在delete时实际也未清除空间
+ 即使对于有指针类型的语言，由于new和delete很耗时，但对于数据大小不敏感，因此可通过Cursor List，在开始时开辟一大块空间，供List使用，以避免频繁new和delete的开销

### 4. Test
+ 测试List功能:
   `cd .../03_list` `g++ test.cpp -o test` `./test`
+ 测试Cursor List功能:
   `cd .../03_list/CursorList` `g++ test.cpp -o test` `./test n`(n为随机初始化List中元素的个数)
   

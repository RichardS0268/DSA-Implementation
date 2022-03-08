# 01 Vector

### 1. Vector Template
>ADT  

![](\1-Vector_Template\Vector-ADT.png)

>Characters
+ Vector是一种典型的线性数据结构，可以将它看做是经过包装的数组。
+ Vector遵循寻秩访问（call by rank）,它在逻辑上和物理上（地址）都是连续的
+ 这一特性使得Vector的静态操作 -- 访问（*visit*），比较（*compare*），而动态操作如插入（insert）删除（*erase*）则比较耗时，worst case均会达到$O(n)$
+ 有序向量能更好地实现查找（$\color{blue}{Search}$），去重等操作。
+ 为了得到有序向量，有各种排序算法（$\color{blue}{Sort}$），同时在插入（*insert*）和删除（*erase*）的时候也都需维护有序性。

### 2. Search
+ 当Vector无序时，只能通过遍历操作来寻找（*find*）,$O(n)$
+ 对于有序向量，可以通过二分查找（*Bin-Search*）, *FibSearch*, *insertSearch* 的算法来优化
+ 各种查找方式都有自己的适用范围，一般我们先通过*插值查找* 迅速将查找范围缩小到一定的尺度，然后进行*二分查找* 进一步缩小范围，最后（当数据项只有200~300时）使用*循序查找*（遍历）。

### 3. Sort
为了得到有序向量，我们需要对Vetor中的元素进行排序，常见的排序方法有
+ `bubbleSort(A[], lo, hi)`;
+ `selectionSort(A[], lo, hi)`;
+ `mergeSort(A[], lo, hi)`;
+ `heapSort(A[], lo, hi)`;
+ `quickSort(A[], lo, hi)`;
+ `shellSort(A[], lo, hi)`;

### 4. Bitmap
+ Bitmap是照应Vector**物理空间连续**特点的一种数据结构，它可以用相对较小的空间存储较大的数据并进行去重，排序等操作。
+ Bitmap的一个缺点在于初始化时Memset(M, 0, N)操作费时，校验环是用空间换取时间的一种方式。
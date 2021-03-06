# Vector

### 1. Characters

+ Vector是一种典型的线性数据结构，可以将它看做是经过包装的数组。
+ Vector遵循寻秩访问（call by rank）,它在逻辑上和物理上（地址）都是连续的
+ 这一特性使得Vector的静态操作如访问（*visit*），比较（*compare*）仅需$O(1)$的时间，而动态操作如插入（insert）删除（*erase*）则比较耗时，worst case时间复杂度均会达到$O(n)$
+ 有序向量能更好地实现查找（$\color{blue}{Search}$），去重等操作。
+ 为了得到有序向量，有各种排序算法（$\color{blue}{Sort}$），同时在插入（*insert*）和删除（*erase*）的时候也都需维护有序性。

### 2. Interface

> ADT接口。同一接口可能有多种具体的实现方式，计算复杂度也不尽相同，详见`Vector.h` 

| 接口            | 功能                                                         | 适用对象 |
| --------------- | ------------------------------------------------------------ | -------- |
| `size()`        | 报告向量当前的规模（元素总数）                               | 向量     |
| `[]`            | 下标运算符重载，寻秩访问                                     | 向量     |
| `insert(r, e)`  | e作为秩为r元素插入，后继元素依次后移                         | 向量     |
| `remove(r)`     | 删去秩为r的元素，返回该元素中原存放的对象                    | 向量     |
| `sort()`        | 调整各元素的位置，使之按非降序排列                           | 向量     |
| `unsort()`      | 随机置乱有序向量中的元素                                     | 有序向量 |
| `find(e)`       | 查找等于e且秩最大的元素                                      | 向量     |
| `search(e)`     | 查找目标元素e，返回不大于e且秩最大的元素                     | 有序向量 |
| `deduplicate()` | 剔除重复元素                                                 | 向量     |
| `uniquify()`    | 剔除重复元素                                                 | 有序向量 |
| `traverse(...)` | 遍历向量并统一处理所有元素，处理方法由参数（函数对象或函数指针）指定 | 向量     |

### 3. Search

+ 当Vector无序时，只能通过遍历操作来寻找（*find*）,$O(n)$
+ 对于有序向量，可以通过二分查找（Bin-Search）的方式来优化
  + Bin-Search_A 将每次查找分为三种情况，包括`_elem[mid] = target`的情况，对此，可以证明当查找的分点为黄金分割比时（$'mid'=\frac{\sqrt{5}-1}{2}$），拥有常数意义上的最低复杂度$O(1.44logn)$，此时也称为Fibonacci查找, 而$'mid'=\frac{1}{2}$时，复杂度为$O(1.5logn)$。
  + 然而Bin-Search_A 并不稳定，有Best case(`_elem[mid] = target` -> $O(1)$)和worst case(target在最后一项 -> $O(2logn)$)，两者之间效率相差很大。
  + 因此我们通常使用Bin_Search_C,它更加**稳定**，复杂度稳定在$O(logn)$水平。
+ 此外，对于较大规模的数据，当其分布较为均匀时，则可使用插值查找的方法
  + 此时[lo, hi]中的元素大致成线性趋势增长，即$$\frac{mi-lo}{hi-lo}\approx\frac{2-A[lo]}{A[hi]-A[lo]}$$
    则可取分点$$mi \approx lo+(hi-lo)·\frac{e-A[lo]}{A[hi]-A[lo]}$$

  + 插值查找的复杂度为$O(loglogn)$
+ 各种查找方式都有自己的适用范围，一般我们先通过*插值查找* 迅速将查找范围缩小到一定的尺度，然后进行*二分查找* 进一步缩小范围，最后（当数据项只有200~300时）使用*循序查找*（遍历）。

### 4. Sort

为了得到有序向量，我们需要对Vetor中的元素进行排序，常见的排序方法有

+ `bubbleSort(A[], lo, hi)`;
  + 时间效率：最好$O(n)$，最坏$O(n^2)$。
  + 当输入含有重复元素时，能保持重复元素的前后顺序，因为bubbleSort只会交换相邻元素，因此算法具有稳定性。
  
    > [算法演示](https://visualgo.net/en/sorting?slide=1)
    > 
    > <img src="https://media.giphy.com/media/eoOiXNwSx0D4e88ZQP/giphy.gif" width="700px" />
  
+ `mergeSort(A[], lo, hi)`;
  + 使用递归的方式，*分而治之*
  + merge操作只需对A扫描一趟，$O(n)$的复杂度，则整体的复杂度为$$T(n)=2T(\frac{n}{2})+O(n)=O(n·logn)$$
  
    > [算法演示](https://visualgo.net/en/sorting?slide=1)
    > 
    > <img src="https://media.giphy.com/media/jA5VMeC1SYgIHt3nXw/giphy.gif" width="600px" />

### 5. Bitmap

+ Bitmap是照应Vector**物理空间连续**特点的一种数据结构，它可以用相对较小的空间存储较大的数据并进行去重，排序等操作。
+ Bitmap的一个缺点在于初始化时`Memset(M, 0, N)`操作费时，校验环是用空间换取时间的一种方式。

### 6. Test

```
g++ test.cpp -o test
./test n (n为随机初始化向量中元素的个数)
```


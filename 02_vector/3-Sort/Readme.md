# Sort
### bubbleSort
+ 时间效率：最好$O(n)$，最坏$O(n^2)$。
+ 当输入含有重复元素时，能保持重复元素的前后顺序，因为bubbleSort只会交换相邻元素，因此算法具有稳定性。

### mergeSort
+ 使用递归的方式，*分而治之*
+ merge操作只需对A扫描一趟，$O(n)$的复杂度，则整体的复杂度为$$T(n)=2T(\frac{n}{2})+O(n)=O(n·logn)$$
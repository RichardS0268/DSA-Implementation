# Bitmap
> C++ 中有<bitset>类，其接口与功能演示：http://c.biancheng.net/view/406.html
### 1. 概述
Bitmap是一种特殊的序列结构，可以动态地表示由一组（无符号整数）构成的几何。其长度无限（对于实际应用场景），且其中每个元素的取值均为布尔型（初始为flase-0）,支持的操作接口主要包括：
+ `void set(int i)`; //将第i个位置置为true（将整数i加入当前集合）
+ `void clead(int i)`; //将第i个位置置为false（从当前几何中删除整数i）
+ `bool test(int i)`; //测试第i个位置是否为true（判断整数i是否属于当前集合）

### 1. 扩展与优化
+ 可以通过校验环(*Bitmap_J.h*)，将初始化的复杂度置为O(1)


### 3. 应用场景：
+ 大数据去重，排序

### 4. 示例
1. test1.cpp: 利用Bitmap和Bitmap_J实现“筛法”寻找整数n(=50)以内的质数
    `g++ test1.cpp -o test1`
    `./test1`
2. test2.cpp: 分别测试Bitmap和Bitmap_J初始化所用时间，以去重任务为例，假设要对一组正数进行去重，且没有先验知识以获取这组数字的取值范围，即有$m = 2^{31}-1=10^9$种可能，则需要初始化Bitmap($10^9$), Bitmap_J($10^9$)。
    `g++ test2.cpp -o test2`
    `./test2`
测试结果：
`init time of Bitmap = 91331 ms`
`init time of Bitmap_J = 25 ms`

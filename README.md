# 算法(第四版) 代码C++实现

[toc]

## 简介

使用 C++ 重写 算法 (第四版) 中的代码 以及 一些笔记

每章目录下是 CodeBlocks 工程，可以使用 CodeBlocks 直接打开

如有不足，恳请指教。
$$
[begin..end] \quad 闭区间 \\
[begin:end]\quad左闭右开区间
$$


## 第一章

### 实现 Queue, Stack, Bag

 **如何使得 Queue, Stack, Bag** 可以使用 **范围 for**

```C++
// 范围 for 其实就是 for 循环的语法糖
vector<int> v= {0, 1, 2, 3, 4, 5, 6, 7, 8, 8};
int sum = 0;
for (auto num: v) sum += num;
// 等价于
for (auto beg = v.begin(), end = V.end(); beg != end; ++beg) {
    auto num = *beg;
    sum += num;
}
```

1. 在Queue, Stack, Bag 中定义嵌套类 **iterator** (访问权限 public)
2. 为 iterator 实现 ***, != , ++** 三个运算符的重载
3. 为 Queue, Stack, Bag 实现 **begin, end** 方法

### 并查集

解决连通问题, 只关注是否连通，不关注之间的路径

## 第三章 查找

### 基于无序链表的顺序查找

### 基于有序数组的二分查找

调整数组大小时可以考虑使用 **移动** 而不是 **拷贝**

### 基于二叉查找树

### 基于红黑树

红黑树的实现可以先参考2-3查找树

### 基于拉链法的散列表

C++ 也有hash 函数(对象)，是 functional 的一个类模板，重载了函数调用运算符，返回值是 T:size_type

### 基于线性探测法的散列表

实现过程中 `keys()` 实现的不够优雅 🤦‍♀️

<center><b>表3.1.11 符号表的各种实现优缺点</b></center>

| 数据结构             | 实现                                       | 优点                                                 | 缺点                                             |
| -------------------- | ------------------------------------------ | ---------------------------------------------------- | ------------------------------------------------ |
| 无序链表             | SequentialSearchST                         | 简单，适用小型问题                                   | 大型符号表操作很慢                               |
| 有序数组<br>二分查找 | BinarySerachST                             | 最优的查找效率和空间需求<br>能够进行有序性相关的操作 | 插入操作太慢                                     |
| 二叉查找树           | BST                                        | 实现简单，<br>能够进行有序性相关的操作               | 没有性能上界的保证<br>链接需要额外的空间         |
| 平衡二叉查找树       | RedBlackBST                                | 最优的查找和插入效率<br>能够进行有序性相关的操作     | 删除算法好麻烦😂<br>链接需要额外的空间            |
| 散列表               | SeparateChainHashST<br>LinearProbingHashST | 能够快速地查找和<br>插入常见类型地数据               | 需要计算每种类型的散列<br>无法进行有序性相关操作 |

<center><b>各测试数据测试结果</b></center>

|                     | tinyTale.txt(60) | tale.txt(135643) | leipzig1M.txt(21191455) |
| ------------------- | :--------------: | :--------------: | :---------------------: |
| SequentialSearchST  |        2         |      20440       |           🤦‍♀️            |
| BinarySerachST      |        2         |       1055       |           🤦‍♀️            |
| BST                 |        2         |       447        |          54216          |
| RedBlackBST         |        2         |       374        |          59980          |
| SeparateChainHashST |        4         |       270        |          37138          |
| LinearProbingHashST |        2         |       294        |          35822          |

**注: 时间单位 clicks**

## 第五章 字符串

字符表 Alphabet

一个字符集就是字符集合，每个字符都对应一个整数，也就是**编码**或者**索引**

**键索引计数排序法**

```C++
// a 为待排序数组, 每个元素的键值在 [0,R-1] 
// key() 为 a[i] 的键值
int n = a.size();
vector<string> aux(n);
int count[R+1];
// 统计每个键出现的次数
// count[i] 即为键 i-1 出现的次数
for (int i = 0; i < n; i++) {
    count[a[i].key() + 1]++;
}
// count[i] 为键 i 的开始索引
for (int r = 1; r <= R; r++) {
    count[r] += count[r-1];
}
// 根据每个元素对应的键值以及 count 数组放置元素到 aux 数组
for (int i = 0; i < n; i++) {
    aux[count[a[i].key()]++] = a[i];
}
// 从 aux 将排好序的元素写回原数组
for (int i = 0; i < n; i++) {
    a[i] = aux[i];
}
```

### 字符串排序

#### 低位优先字符串排序

稳定排序，必须扫描完整个字符串，一般适用于 等长字符串

假设最大字符串长度为 W，那么 LSD字符串排序将进行 W 轮**键索引计数排序**

#### 高位优先的字符串排序

稳定排序

假设字符串的字符集大小为 R

那么高位优先字符串的递归过程就是一个 R叉树 深度优先搜索，花费空间取决于树的高度(递归栈深度)，花费的时间取决于树上有多少结点，每一个结点都进行一次**键索引计数排序法**

不能很好的处理等值键，有较长公共前缀的键，取值范围比较小的键和小数组

#### 三向字符串快速排序

通用的，性能较好的字符串 原地排序不稳定

## 日志

**2020年09月28日** 

​	Queue, Stack, Bag, UnionFind

**2020年09月29日** 

​	符号表无序链表的顺序查找

**2020年09月30日** 

​	二分查找符号表

**2020年10月02日**  

​	二叉查找树 😂😂 求求你了 认真点 别写 BUG 了🤦‍♀️

**2020年10月04日** 

​	红黑树 🙃🙃红黑树删除操作有点男

​	目前基于二分搜索版本的符号表不能处理测试数据 leipzig1M.txt ❓

​	当前版本红黑树和二分查找树效率为什么差不多？❓

**2020年10月05日**

​	拉链法的散列表

​    目前基于拉链法的散列表的符号表也🙃🙃不能处理测试数据 leipzig1M.txt✅ 

**2020年10月07日**

​	线性探测法的散列表

​	基于拉链法的散列表的符号表不能处理 Leipzig1M.txt 是因为, 使用的是他的默认大小 997,  对于大量数据

​	一个桶上的链越来越长，所以无法处理。只需调整其大小即可。

**2020年10月09日**

​	字符串排序 LSD MSD 三向字符串快速排序

​	该传引用时🙅‍忘记 `&`


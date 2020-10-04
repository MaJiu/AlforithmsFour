# 算法(第四版) 代码C++实现

[toc]

## 简介

使用 C++ 重写 算法 (第四版) 中的代码 以及 一些笔记

每章目录下是 CodeBlocks 工程，可以使用 CodeBlocks 直接打开

如有不足，恳请指教。

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

## 日志

2020年09月28日 

​	Queue, Stack, Bag, UnionFind

2020年09月29日 

​	符号表无序链表的顺序查找

2020年09月30日 

​	二分查找符号表

2020年10月02日  

​	二叉查找树 😂😂 求求你了 认真点 别写 BUG 了

2020年10月04日 

​	红黑树 🙃🙃红黑树删除操作有点男

​	目前基于二分搜索版本的符号表不能处理测试数据 leipzig1M.txt

​	当前版本红黑树和二分查找树效率为什么差不多？
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

## 日志

2020年9月28日 Queue, Stack, Bag, UnionFind
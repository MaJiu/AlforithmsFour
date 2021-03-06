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

### 单词查找树

#### 基于单词查找树的符号表

请牢记这个错误❌

```C++
constexpr int R = 128;
for (char ch = 0; ch < R; ch++) {
    // ...
}
// char [-128, 127] ch会溢出
```

单词查找树是通过链接隐式的存储字符串，一般会有一个 ’**哑根节点**‘，键最后一个字母所在的结点深度(根节点深度为 0)比键和键的唱的相等

单词查找树的链表结构和键的插入或删除顺序无关，对于任意给定的一组键，其单词查找树都是唯一的

查找或插入一个键，访问数组的次数最多位键的长度加1

字母表的大小为 $R$  ,在一棵由$N$个随机键构造的单词查找树中，未命中查找平均所需的结点数为 $\sim$$\log_RN$

一棵单词查找树中的链接总数在 $RN$ 和 $RNw$ 之间，其中 $w$ 为键的长度

可以想象只有一个字母的键集，且每个键字母都不同，那么每一个键都会单独成一个结点，一个结点有一个大小为 $R$ 的指针数组

**适用于较短的键和较小的字母表**

#### 基于三向单词查找树的符号表

字符显示的保存在结点元素中

左子树是首字母比当前结点字母小的键，右子树是首字母比当前结点字母大的键，

中子树是以结点字母为首字母的键，所以沿着中间链接前进时才会找到键

由 $N$ 个平均长度为$w$的字符串构造的三向单词查找树的链接总数在  $3N$ 到 $3Nw$ 之间，可以想象只有一个字母的键集，且每个键字母都不同，此时的单词查找树就是一个键是字母的二叉查找树

在一棵由 $N$ 个随机字符串构造的三向单词查找树种，查找未命中需要比较字符 $\sim$$\ln N$

**可以将单词查找树和三向单词查找树混合使用，组织成森林的形式**

三向单词查找树和三向字符排序有一定联系，单词查找树和高位优先字符串排序有着一定的联系

### 子字符串查找

```C++
// 暴力
int search(const string &txt, const string &pat)
{
    int m = pat.size();
    int n = txt.size();
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (pat[j] != txt[j]) break;
		}
        if (j == m) return i; // 匹配成功
    }
    return n; // 匹配失败
}

// 暴力--显示回退
int search(const string &txt, const string &pat)
{
    int m = pat.size();
    int n = txt.size();
    int i, j;
    for (i = 0, j = 0; i < n && j < m; i++) {
        if (txt[i] == pat[j]) j++; // 前进
        // KMP 算法不会让 i 回退, 省略了回退然后重新匹配的过程
        else { i -= j; j = 0; } // 回退
    }
    if (j == m) return i - m; // 找到匹配
    else return n; // 匹配失败
}
```

从暴力算法的结构来看，子字符串查找算法主要有两个步骤

1. 寻找起始位置，文本长度为 $$n$$，模式长度为 $$m$$，那么其实位置 $$i$$ 可以为 $$[0, n - m]$$，共计 $$n-m+1$$个
2. 内循环对比文本字符串` txt[i:i+m]` 是否和 模式相等，最多比较 $$m$$ 次

KMP算法是对步骤2的优化，根据前面匹配失败的信息，使得内循环没必要每次从头开始

Boyer-Moore 算法是对步骤1的优化

#### KMP算法

Knuth-Morris-Pratt 子字符串查找算法

**版本:	完整的DFA**

考虑 **暴力--回显** 版本，当一次匹配失败时，会将 i 退回开始位置，j 置 0(也相当于退回开始位置)。此次匹配虽然失败但不是毫无意义，我们得知了 `txt[i-j:i] == pat[:j]` 

KMP算法保证 再 不回退 i 的情况下，调整 j 使得匹配可以继续进行，如何调整 j，核心在于 DFA

**如何构建 DFA 数组？**

**给定一个输入字符串，DFA 最终都会停在一个状态上**

`dfa[c][s]` 为状态 `s` 在遇到字符 `c` 后转移的状态

dfa 数组的构造是递推的，也就是说如果我们有模式 `pat1`，他所对应的确定有限自动机为 `dfa1`，现有模式 `pat2, 且 pat2 == pat1 + "A"`，那么我们可以方便地由 `dfa1` 构造出 `pat2` 对应的 `dfa2`

给 `dfa1` 添加状态新状态 `S`, 当下一个字母为 A，即匹配成功时，`dfa1` 的结束状态 `END` 转移至状态 `S`，当匹配失败时，`END` 的转移和他的**重启状态** `R` 相同 ，`R` 就是 状态 `END` 匹配失败能回退到的**最近**的状态 ，也就是从开始状态 `BEING`， 经历输入为 `pat1[1:]` 时 `dfa1` 停止的状态 ( `END` 是输入为 `pat1` 时 `dfa1` 停止的状态，那么此时匹配失败，将状态机置为初始状态，从下一个字符`pat[1]` 开始重新开始匹配，此时停止状态就是 `R`)。

当 `len(pat) == 2 || len(pat) == 3`时，DFA 是显然的，当 `len(pat) > 3` 时，对应的 DFA 可以从前一个DFA 构造出

DFA 数组的构造核心有两点

1. 状态 `S` 的重启状态为 `R`，那么当匹配失败时 `dfa[c][S] == dfa[c][R]`，`c` 为所有让匹配失败的字符
2. 状态 `S1` 的重启状态为 `R1`, 状态 `S2 == dfa[c][S1]` 那么有 `R2 == dfa[c][R1]`

`END` 的转移和他的**重启状态** `R` 相同的含义时，回到初始位置，从下一个字符重新开始匹配达到状态`R`，状态 `R` 面对此次失败的匹配回怎样转移，`END` 就进行怎样转移

#### Boyer-Moore (非完整版)

**版本: 启发式的查找不匹配的字符**

从右向左进行匹配，匹配失败时，根据 `right` 数组最大化地将模式向右移动，尽可能寻找比较远的的下一个起始位置，假设当前文本匹配失败的字符为 `char1`，原本的暴力算法，当匹配失败时，将模式向右移动 1 位 (i++)，模式右移后，模式会有一个新的字符 `char2`和 `char1` 对齐，但有可能两个不相等，也就是说此次重新开始时的匹配注定还是失败的，这样还不如将模式多向右移动几位，最起码保证新对齐的两个字符相等。

**目前只对当前匹配失败的字符进行了启发式查找**

在一般情况下，BM 算法通过启发式处理不匹配字符需要 $$\sim N/M$$ 次字符比较，最差需要 $$NM$$，例如给定文本

AAAAAAAAAAAAAAAAAAAAAABAAAAA，和模式 BAAAAA

#### Rabin-Karp 指纹字符串查找算法

核心思想 通过计算散列值判断文本的一个子串和模式是否相等

关键点在于利用模运算性质简化散列值计算

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

**2020年10月11日**

​	基于单词查找树的符号表 

​	基于三向单词查找树的符号表

**2020年10月12日**

​	KMP 算法	很精巧，有限状态自动机也很值得研究，编译原理也有讲到过

**2020年10月15日**

​	Boyer-Moore 字符串匹配算法

​	Rabin-Karp 指纹字符串查找算法

​	蒙特卡洛算法 和 拉斯维加斯算法？


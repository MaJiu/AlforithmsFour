#include <string>
#include <vector>
#include "MSD.h"

// 2020-10-09-21.00
// 高位优先的字符串排序


static int get_index(std::string &str, int index);
static void msd_sort(std::vector<std::string> &strs, int lo, int hi, int i);

constexpr int R = 128;
constexpr int Threshold = 15; // 小数组的切换阈值
std::vector<std::string> aux;

void msd_sort(std::vector<std::string> &strs)
{
    int n = strs.size();
    if (n <= 1) return;
    aux.resize(n);
    msd_sort(strs, 0, n-1, 0);
}

// 闭区间 排序strs[lo..hi]
static void msd_sort(std::vector<std::string> &strs, int lo, int hi, int i)
{
    if (hi <= lo) return;
    int count[R+2]{0};

    // count[i] 为字符 ASCII[i-2] 的数量
    // count[1] 为长度等于 i 的字符串
    for (int j = lo; j <= hi; j++) {
        count[get_index(strs[j], i)+2]++;
    }

    // count[0] 为长度等于 i 的字符串在 aux数组 的起始索引
    // count[i] 为以字符 ASCII[i] 为关键字时包含该字符的字符串在 aux数组 的起始索引
    for (int j = 1; j <= R+1; j++) {
        count[j] += count[j-1];
    }

    // 根据 count数组 放置各字符串
    for (int j = lo; j <= hi; j++) {
        aux[count[get_index(strs[j], i)+1]++] = strs[j];
    }

    // 回写
    for (int j = lo; j <= hi; j++) {
        strs[j] = aux[j - lo];
    }
    // 以首字母分割数组 对子数组进行排序
    for (int j = 1; j <= R; j++) {
        msd_sort(strs, lo + count[j-1], lo + count[j] - 1, i+1);
    }
}

/**
* 获取字符 str[index] 的 ASCII码, 即该字符对应的索引, 也就是他在 count 数组的位置
* 如果 index >= str.size(), 返回 -1
*/
static int get_index(std::string &str, int index)
{
    int length = str.size();
    if (index >= length) return -1;
    return static_cast<int>(str[index]);
}

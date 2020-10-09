#include <string>
#include <vector>
#include "LSD.h"

// 2020-10-09-20.55
// 算法5.1 低位优先的字符串排序


static int get_index(std::string &str, int index);

constexpr int R = 128;
void lsd_sort(std::vector<std::string> &strs)
{
    int n = strs.size();
    if (n <= 1) return;

    int max_length = strs.front().size();
    for (auto &s : strs) max_length = std::max(static_cast<int>(s.size()), max_length);

    std::vector<std::string> aux(n);
    for (int i=max_length-1; i >= 0; i--) {
        int count[R+2]{0};
        // count[i] 为字符 ASCII[i-2] 的数量
        // count[1] 为长度小于 i 的字符串
        for (auto &s: strs) {
            count[get_index(s, i)+2]++;
        }
        // count[0] 为长度小于 i 的字符串在 aux数组 的起始索引
        // count[i] 为以字符 ASCII[i] 为关键字时包含该字符的字符串在 aux数组 的起始索引
        for (int j = 1; j <= R+1; j++) {
            count[j] += count[j-1];
        }
        // 根据 count数组 放置各字符串
        for (auto &s: strs) {
            aux[count[get_index(s, i)+1]++] = s;
        }
        std::swap(aux, strs);
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

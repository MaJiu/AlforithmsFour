#include <vector>
#include <string>


namespace {
    /**
    * 获取字符 str[index] 的 ASCII码, 即该字符对应的索引
    * 如果 index >= str.size(), 返回 -1
    */
    static int get_index(std::string &str, int index)
    {
        int length = str.size();
        if (index >= length) return -1;
        return static_cast<int>(str[index]);
    }

    void quick3_sort(std::vector<std::string> &strs, int lo, int hi, int index)
    {
        if (hi <= lo) return;
        int left = lo;
        int right = hi;
        int i = lo+1;
        int v = get_index(strs[lo], index);
        /**
        * loop invariant 循环不变式
        * [lo..left-1] < v == [left..i-1] < [right+1..hi]
        * [i..right] 未知
        */
        while (i <= right) {
            int cur = get_index(strs[i], index);
            if (cur < v) std::swap(strs[i++], strs[left++]);
            else if (cur > v) std::swap(strs[i], strs[right--]);
            else i++;
        }
        quick3_sort(strs, lo, left-1, index); // 小于 V 的那一组
        // 如果以 V 为首的字符串长度大于 index, 那么忽视首字母, 继续排序
        if (v >= 0) quick3_sort(strs, left, i-1, index+1);
        quick3_sort(strs, right+1, hi, index);
    }

}

void quick3_sort(std::vector<std::string> &strs)
{
    int n = strs.size();
    if (n <= 1) return;
    quick3_sort(strs, 0, n-1, 0);
}


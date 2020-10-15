#ifndef BOYERMOORE_H_INCLUDED
#define BOYERMOORE_H_INCLUDED

#include <string>
// 2020-10-15-20.55
// 算法 5.7 Boyer-Moore 字符串匹配算法 启发式地处理不匹配字符

class BoyerMoore {
private:
    static constexpr int R_ = 128;
    int right_[R_];
    std::string pattern_;

public:
    BoyerMoore(const std::string &pat);
    int search(const std::string &txt);
};
#endif // BOYERMOORE_H_INCLUDED

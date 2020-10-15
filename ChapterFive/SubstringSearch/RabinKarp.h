#ifndef RABINKARP_H_INCLUDED
#define RABINKARP_H_INCLUDED

#include <string>

// 2020-10-15-20.19
// 算法 5.8 指纹字符串查找算法

class RabinKarp {
private:
    static constexpr int R_ = 128;
    std::string pattern_;
    long long pat_hash_; // 模式的散列值
    long long RM_; // R^(m_-1) % Q
    int m_; // 模式长度
    int Q_; // 一个很大的素数

    bool check(int index);
    bool check(const std::string &txt, int index);
    long long hash(const std::string &key, int m);

public:
    RabinKarp(const std::string &pat);
    int search(const std::string &txt);

};
#endif // RABINKARP_H_INCLUDED

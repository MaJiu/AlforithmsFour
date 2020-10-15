#include "RabinKarp.h"

// 蒙特卡洛算法
bool RabinKarp::check(int index)
{

    return true;
}

// 拉斯维加斯算法
bool RabinKarp::check(const std::string &txt, int index)
{
    for (int i = 0; i < m_; i++) {
        if (txt[index+i] != pattern_[i]) return false;
    }
    return true;
}

// 散列函数
long long RabinKarp::hash(const std::string &key, int m)
{
    long long h = 0;
    for (int i = 0; i < m; i++) {
        h = (R_ * h + key[i]) % Q_;
    }
    return h;
}

RabinKarp::RabinKarp(const std::string &pat)
{
    pattern_ = pat;
    m_ = pat.size();
    Q_ = 100000007; // 这里暂时偷懒固定了一个不是很大的素数
    RM_ = 1;
    for (int i = 1; i <= m_-1; i++) {
        RM_ = (R_ * RM_) % Q_;
    }
    pat_hash_ = hash(pat, m_);
}

int RabinKarp::search(const std::string &txt)
{
    int n = txt.size();
    long long txt_hash = hash(txt, m_);
    if (txt_hash == pat_hash_ && check(txt, 0)) return 0;
    for (int i = m_; i < n; i++) {
        txt_hash = (txt_hash + Q_ - RM_ * txt[i-m_] % Q_) % Q_; //  加 Q 可以避免出现负数
        txt_hash = (txt_hash * R_ + txt[i]) % Q_;
        if (txt_hash == pat_hash_ && check(txt, i - m_ + 1)) return i - m_ + 1;
    }
    return n;
}

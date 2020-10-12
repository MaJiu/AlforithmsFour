#ifndef KMP_H_INCLUDED
#define KMP_H_INCLUDED
#include <string>

class KMP {
private:
    std::string pattern_;
    static constexpr int R_ = 128;
    const int M_;
    int* dfa_[R_];

public:
    KMP(const std::string &pat);
    ~KMP();
    int search(const std::string &txt);
};
#endif // KMP_H_INCLUDED

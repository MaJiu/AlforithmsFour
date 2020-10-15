#include "BoyerMoore.h"


BoyerMoore::BoyerMoore(const std::string &pat)
{
    pattern_ = pat;
    int m = pat.size();
    for (int c = 0; c < R_; c++) {
        right_[c] = -1;
    }
    for (int i = 0; i < m; i++) {
        right_[static_cast<int>(pat[i])] = i;
    }
}

int BoyerMoore::search(const std::string &txt)
{
    int n = txt.size();
    int m = pattern_.size();
    int skip;
    for (int i = 0; i <= n-m; i += skip) {
        skip = 0;
        for (int j = m-1; j >= 0; j--) {
            if (txt[i+j] != pattern_[j]) {
                skip = j - right_[static_cast<int>(txt[i+j])];
                if (skip < 1) skip = 1;
                break;
            }
        }
        if (skip == 0) return i;
    }
    return n;
}

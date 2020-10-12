#include "KMP.h"


KMP::KMP(const std::string &pat): pattern_(pat), M_(pat.size()) {
        for (auto &line_ptr: dfa_) {
            line_ptr = new int[M_]();
        }
        // 构造 DFA
        dfa_[static_cast<int>(pat[0])][0] = 1;
        // 初始 j 为状态 1, X 为 j 的重启状态
        for (int X = 0, j = 1; j < M_; j++) {
            for (int c = 0; c < R_; c++) {
                dfa_[c][j] = dfa_[c][X];
            }
            dfa_[static_cast<int>(pat[j])][j] = j+1;
            X = dfa_[static_cast<int>(pat[j])][X]; // 获取 j+1 的重启状态
        }
    }

KMP::~KMP() {
        for (auto line_ptr: dfa_) delete[] line_ptr;
    }


int KMP::search(const std::string &txt) {
    int N = txt.size();
    int i, j;
    for (i = 0, j = 0; i < N && j < M_; i++) {
        j = dfa_[static_cast<int>(txt[i])][j];
    }
    if (j == M_) return i - M_;
    return N;
}


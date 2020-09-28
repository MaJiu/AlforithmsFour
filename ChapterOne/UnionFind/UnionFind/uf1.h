#ifndef UF1_H_INCLUDED
#define UF1_H_INCLUDED

// 2020-09-28-19.34
// quick find
// 当且仅当 id[p] == id[q] 时, p, q 是连通的
// id[i] 为 i 所在的连通分量
class UF {
    int *id_;
    int n_;
    int count_;

public:
    UF(int n): n_(n), count_(n) {
        id_ = new int[n];
        for (int i=0; i < n; i++) id_[i] = i;
    }
    ~UF() { delete[] id_; }
    int count() { return count_; }
    int find(int p) {
        return id_[p];
    }
    void uunion(int p, int q) {
        int pid = find(p);
        int qid = find(q);
        if (pid == qid) return; // 已经连通
        for (int i=0; i<n_; i++) if (id_[i] == pid) id_[i] = qid;
        count_--;
    }
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
};

#endif // UF1_H_INCLUDED

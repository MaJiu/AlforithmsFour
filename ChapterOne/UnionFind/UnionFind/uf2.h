#ifndef UF2_H_INCLUDED
#define UF2_H_INCLUDED

// 2020-09-28-20.14
// quick-union 算法
// 父链接树 id[i] 为 i 的父结点,
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

    // 查找 p 所在树的根节点
    int find(int p) {
        while ( id_[p] != p) p = id_[p];
        return p;
    }
    void uunion(int p, int q) {
        int proot = find(p);
        int qroot = find(q);
        if (proot == qroot) return;
        // 把 树proot 接在 树root
        id_[proot] = qroot;
        count_--;
    }
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
};
#endif // UF2_H_INCLUDED

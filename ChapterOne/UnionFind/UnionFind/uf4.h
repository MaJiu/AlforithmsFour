#ifndef UF4_H_INCLUDED
#define UF4_H_INCLUDED

// 2020-09-28-20.35
// 使用路径压缩的加权 quick-union 算法
class UF {
    int *id_;
    int *sz_;
    int n_;
    int count_;

public:
    UF(int n): n_(n), count_(n) {
        id_ = new int[n];
        sz_ = new int[n];
        for (int i=0; i < n; i++) {
            id_[i] = i;
            sz_[i] = 1;
        }
    }
    ~UF() { delete[] id_; delete[] sz_;}
    int count() { return count_; }

    // 查找 p 所在树的根节点
    int find(int p) {
//        while ( p != id_[p] ) {
//            id_[p] = id_[id_[p]];
//            p = id_[p];
//        }
//        return p;

       //递归写法
       if (p == id_[p]) return p;
       id_[p] = find(id_[p]);
       return id_[p];

    }
    void uunion(int p, int q) {
        int proot = find(p);
        int qroot = find(q);
        if (proot == qroot) return;
        // 根据两棵树的大小进行合并
        if (sz_[proot] > sz_[qroot]) {
            id_[qroot] = proot;
            sz_[proot] += sz_[qroot];
        } else {
            id_[proot] = qroot;
            sz_[qroot] += sz_[proot];
        }
        count_--;
    }
    bool connected(int p, int q) {
        return find(p) == find(q);
    }
};

#endif // UF4_H_INCLUDED

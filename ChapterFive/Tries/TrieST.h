#ifndef TRIEST_H_INCLUDED
#define TRIEST_H_INCLUDED

#include <string>
#include <vector>
// 2020-10-10-21.18
// 算法 5.4 基于单词查找树的符号表

template <typename V>
class TrieST {
private:
    static constexpr int R = 128;
    struct Node {
        V *val;
        Node *next[R]{nullptr};
        Node(): val(nullptr) {}
        Node(const &v) { val = new V(val);

        }
        ~Node() {
            delete val;
            // 这样写这可以递归的销毁 Trie
            for (auto ptr: next) if (ptr != nullptr) delete ptr;
        }
    };
    int size_;
    Node *root_;

public:
    TrieST(): size_(0) { root_ = new Node();}
    ~TrieST() { if (root_ != nullptr) delete root_;}
    // TODO 拷贝构造函数 重载赋值运算符函数

    V* get(const std::string &key) {
        Node *x = get(root_, key, 0);
        return x == nullptr ? nullptr : x->val;
    }

    void put(const std::string &key, const V &val) {
        root_ = put(root_, key, val, 0);
    }

    std::vector<std::string> keys_with_prefix(const std::string &pre) {
        std::vector<std::string> ks;
        std::string temp_string(pre);
        // 先找到起点
        collect(get(root_, pre, 0), temp_string, ks);
        return ks;
    }

    std::vector<std::string> keys() {
        return keys_with_prefix("");
    }

    std::vector<std::string> keys_that_match(const std::string pattern) {
        std::vector<std::string> ks;
        std::string string_temp;
        collect(root_, string_temp, pattern, ks);
        return ks;
    }

    std::string longest_prefix(const std::string &s) {
        int length = search(root_, s, 0, 0);
        return s.substr(0, length);
    }

    void ddelete(const std::string &key) {
        root_ = ddelete(root_, key, 0);
    }
    bool contains(const std::string &key) { return get(key) != nullptr;}
    bool empty() { return size_ == 0; }
    int size() { return size_; }

private:
    Node* get(Node *x, const std::string &key, int d);
    Node* put(Node *x, const std::string &key, const V &val, int d);
    void collect(const Node *x, std::string &str, std::vector<std::string> &ks);
    void collect(const Node *x, std::string &str, const std::string &pat, std::vector<std::string> &ks);
    int search(const Node *x, const std::string &s, int d, int length);
    Node* ddelete(Node *x, const std::string &key, int d);
};

// 根据 key 的指引从上往下查找
/**
*   @param d: 当前已经查找过的字符数 递归深度
*   @return 路径为 key 的结点
*/
template <typename V>
typename TrieST<V>::Node* TrieST<V>::get(Node *x, const std::string &key, int d)
{
    if (x == nullptr) return nullptr;
    if (static_cast<size_t>(d) == key.size()) return x;
    char ch = key[d];
    return get(x->next[static_cast<int>(ch)], key, d+1);
}

template <typename V>
typename TrieST<V>::Node* TrieST<V>::put(Node *x, const std::string &key, const V &val, int d)
{
    if (x == nullptr) x = new Node();
    if (static_cast<size_t>(d) == key.size()) {
        if (x->val == nullptr) {
            x->val = new V(val);
            size_++;
            return x;
        }
        *(x->val) = val;
        return x;
    }
    char ch = key[d];
    x->next[static_cast<int>(ch)] = put(x->next[static_cast<int>(ch)], key, val, d+1);
    return x;
}


/**
*   @param str: 根结点到当前结点路经上所有结点连成的字符串
*/
template <typename V>
void TrieST<V>::collect(const Node *x, std::string &str, std::vector<std::string> &ks)
{
    if (x == nullptr) return;
    if (x->val != nullptr) ks.push_back(str);
    /**
    * Bug fix
    * for (char ch = 0; ch < R; ch++) 溢出错误 char 范围[-128,127]
    */
    for (int ch = 0; ch < R; ch++) {
        str.push_back(ch);
        collect(x->next[ch], str, ks);
        str.pop_back();
    }
}

/**
*   @param pat 含有通配符 '.' 的模式串 一个 '.' 可以匹配任何字符串
*   @param str: 根结点到当前结点路经上所有结点连成的字符串
*/
template <typename V>
void TrieST<V>::collect(const Node *x, std::string &str, const std::string &pat, std::vector<std::string> &ks)
{
    if (x == nullptr) return;
    if (str.size() == pat.size() && x->val != nullptr) {
        ks.push_back(str);
        return;
    }
    if (str.size() == pat.size()) return;
    char ch = pat[str.size()];
    if (ch == '.') {
        for (int c = 0; c < R; c++) {
            str.push_back(c);
            collect(x->next[c], str, pat, ks);
            str.pop_back();
        }
    }
    else {
        str.push_back(ch);
        collect(x->next[static_cast<int>(ch)], str, pat, ks);
        str.pop_back();
    }
}

/**
*   @param d 递归深度
*   @param length: 当前最长前缀长度
*   @return 最长前缀长度
*/
template <typename V>
int TrieST<V>::search(const Node *x, const std::string &s, int d, int length)
{
    if (x == nullptr) return length;
    if (x->val != nullptr) length = d; // 发现一个键就更新最长前缀长度
    if (static_cast<size_t>(d) == s.size()) return length; // 搜索结束返回
    return search(x->next[static_cast<int>(s[d])], s, d+1, length);

}


template <typename V>
typename TrieST<V>::Node* TrieST<V>::ddelete(Node *x, const std::string &key, int d)
{
    if (x == nullptr) return x;
    // 找到了 进行删除
    if (static_cast<size_t>(d) == key.size() && x->val != nullptr) {
        delete x;
        x = nullptr;
        size_--;
        return x;
    }
    if (static_cast<size_t>(d) == key.size()) return x; // 没有该键
    // 继续查找
    int c = key[d];
    x->next[c] = ddelete(x->next[c], key, d+1);
    if (x->val != nullptr) return x; // 该结点还保留一个键 仍然有用
    // 否则检查该结点是否有其他分支 如果没有则删除
    for (int i = 0; i < R; i++) {
        if (x->next[i] != nullptr) return x; // 有分支 保留
    }
    delete x;
    x = nullptr;
    return x;
}
#endif // TRIEST_H_INCLUDED

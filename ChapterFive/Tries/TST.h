#ifndef TST_H_INCLUDED
#define TST_H_INCLUDED

// 2020-10-11-20.04
// 基于三向单词查找树的符号表

#include <string>
#include <vector>

template <typename V>
class TST {
private:
    struct Node {
        char c;
        Node* left;
        Node* mid;
        Node* right;
        V *val;
        Node(): c('\0'), left(nullptr), mid(nullptr), right(nullptr), val(nullptr) {  }
        ~Node() {
            if (left != nullptr) delete left;
            if (mid != nullptr) delete mid;
            if (right != nullptr) delete right;
            if (val != nullptr) delete val;
        }
    };
    Node *root_;
    int size_;

public:
    TST(): root_(nullptr), size_(0) {}
    ~TST() { if (root_ != nullptr) delete root_;}
    // TODO 拷贝构造函数 赋值运算符重载函数

    V* get(const std::string &key) {
        Node *x = get(root_, key, 0);
        return x == nullptr ? nullptr : x->val;
    }
    void put(const std::string &key, const V &val) {
        root_ = put(root_, key, val, 0);
    }

    std::vector<std::string> keys_with_prefix(const std::string &pre);

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

    void ddelete(const std::string &key); // TODO 删除一个键
    bool empty() { return size_ == 0; }
    int size() { return size_; }
    bool contains(const std::string &key) { return get(key) != nullptr;}


private:
    Node* get(Node *x, const std::string &key, int d);
    Node* put(Node *x, const std::string &key, const V &val, int d);
    void collect(const Node *x, std::string &str, std::vector<std::string> &ks);
    void collect(const Node *x, std::string &str, const std::string &pat, std::vector<std::string> &ks);
    int search(const Node *x, const std::string &s, int d, int length);

};


/**
*   @param d 当前匹配成功的字符数
*/
template <typename V>
typename TST<V>::Node* TST<V>::get(Node *x, const std::string &key, int d)
{
    if (x == nullptr) return nullptr;
    char ch = key[d];
    if (ch < x->c) return get(x->left, key, d);
    else if (ch > x->c) return get(x->right, key, d);
    d++; // ch == x->c 匹配上 key[d]
    if (static_cast<size_t>(d) < key.size()) return get(x->mid, key, d); // 没有结束继续查找
    return x; // 匹配结束
}


template <typename V>
typename TST<V>::Node* TST<V>::put(Node *x, const std::string &key, const V &val, int d)
{
    char ch = key[d];
    if (x == nullptr) {
        x = new Node();
        x->c = ch;
    }
    if (ch < x->c) x->left = put(x->left, key, val, d);
    else if (ch > x->c) x->right = put(x->right, key, val, d);
    else {
        d++; // 又成功匹配一个字符
        if (static_cast<size_t>(d) < key.size()) x->mid = put(x->mid, key, val, d);
        // 已经找到
        else if (x->val == nullptr) {
            x->val = new V(val);
            size_++;
        }
        else *(x->val) = val;
    }
    return x;
}

template <typename V>
std::vector<std::string> TST<V>::keys_with_prefix(const std::string &pre)
{
    std::vector<std::string> ks;
    std::string temp_string;
    Node *start = root_;
    if (pre.size() != 0) {
        temp_string = pre;
        // 中子树全是以 pre 为前缀的数
        start = get(root_, pre, 0)->mid;
    }
    collect(start, temp_string, ks);
    return ks;
}

template <typename V>
void TST<V>::collect(const Node *x, std::string &str, std::vector<std::string> &ks)
{
    if (x == nullptr) return;
    str.push_back(x->c);
    if (x->val != nullptr) ks.push_back(str);
    // 收集首字母是 x->c 的键
    collect(x->mid, str, ks);
    str.pop_back();
    // 收集首字母比 x->c 小的键
    collect(x->left, str, ks);
    // 收集首字母比 x->c 大的键
    collect(x->right, str, ks);
}

template <typename V>
void TST<V>::collect(const Node *x, std::string &str, const std::string &pat, std::vector<std::string> &ks)
{
    if (x == nullptr) return;
    if (str.size() == pat.size()) {
        return;
    }
    char ch = pat[str.size()];
    if (ch == '.') {
        str.push_back(x->c);
        if (str.size() == pat.size() && x->val != nullptr) {
            ks.push_back(str);
            str.pop_back();
            return;
        }
        // 收集首字母是 x->c 的键
        collect(x->mid, str, pat, ks);
        str.pop_back();
        // 收集首字母比 x->c 小的键
        collect(x->left, str, pat, ks);
        // 收集首字母比 x->c 大的键
        collect(x->right, str, pat, ks);

    } else {
        str.push_back(ch);
        if (str.size() == pat.size() && x->val != nullptr) {
            ks.push_back(str);
            str.pop_back();
            return;
        }
        collect(x->mid, str, pat, ks);
        str.pop_back();
    }
}

/**
*   @param d 当前匹配成功的字符数
*/
template <typename V>
int TST<V>::search(const Node *x, const std::string &s, int d, int length)
{
    if (x == nullptr) return length;
    char ch = s[d];
    if (ch < x->c) return search(x->left, s, d, length);
    if (ch > x->c) return search(x->right, s, d, length);
    d++;
    if (x->val != nullptr) length = d;
    if (static_cast<size_t>(d) < s.size()) return search(x->mid, s, d, length);
    return length;
}
#endif // TST_H_INCLUDED

#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <vector>

// 2020-10-02-15.01
// 算法3.3 基于二叉查找树的符号表

template <typename K, typename V>
class BST{
private:
    struct Node {
        K key;
        V *val;
        Node *left;
        Node *right;
        // 左子树的 size 就是该节点在以其为根节点的树的排名
        int size; // 以该节点为根节点的树的节点数 配合 select rank size 等成员函数
        Node(const K &k, const V &v, int n=1, Node *l=nullptr, Node *r=nullptr):
            key(k), left(l), right(r), size(n)
            { val = new V(v); }
        ~Node() { delete val; }
    };
    Node *root;

public:
    BST(): root(nullptr) {}
    ~BST() { clear(root); }
    // TODO 拷贝构造函数 和 赋值运算符重载函数


    bool contains(const K &key) { return get(key) != nullptr; }
    int empty() { return size(root) == 0; }
    int size() { return size(root); }

    V* get(const K &key) { return get(root, key); }
    void put(const K &key, const V &val) { root = put(root, key, val); }
    void delete_min() { root = delete_min(root); }
    void delete_max() { root = delete_max(root); }
    // Hibbard 算法
    void ddelete(const K &key) { root = ddelete(root, key); }

    // 这些函数都可能会出错 访问空指针
    K min() { return min(root)->key; }
    K max() { return max(root)->key; }
    K floor(const K &key) { return floor(root, key)->key; }
    K ceil(const K &key) { return ceil(root, key)->key; }
    K select(int i) { return select(root, i)->key; }

    int rank(const K &key) { return rank(root, key); }
    vector<K> keys() { return keys(min(), max()); }
    vector<K> keys(const K &lo, const K &hi) {
        vector<K> ks;
        keys(root, ks, lo, hi);
        return ks;
    }

private:
    void clear(const Node *troot) {
        if (troot == nullptr) return;
        clear(troot->left);
        clear(troot->right);
        delete troot;
    }

    int size(const Node *troot) {
        if (troot == nullptr) return 0;
        return troot->size;
    }

    V* get(const Node *troot, const K &key);
    Node* put(Node *troot, const K &key, const V &val);
    Node* delete_min(Node *troot);
    Node* delete_max(Node *troot);
    Node* ddelete(Node *troot, const K &key);

    Node* min(Node *troot) {
        if (troot->left == nullptr) return troot;
        return min(troot->left);
    }

    Node* max(Node *troot) {
        if (troot->right == nullptr) return troot;
        return max(troot->right);
    }

    Node* floor(Node *troot, const K &key);
    Node* ceil(Node *troot, const K &key);
    Node* select(Node *troot, int i);

    int rank(const Node *troot, const K &key);
    void keys(const Node* troot, vector<K> &ks, const K &lo, const K &hi);
};

template <typename K, typename V>
V* BST<K, V>::get(const Node* troot, const K &key)
{
    if (troot == nullptr) return nullptr;
    if (troot->key == key) return troot->val;
    if (troot->key < key) return get(troot->right, key);
    return get(troot->left, key);
}

template <typename K, typename V>
// 需要加上typename 不然无法通过编译
typename BST<K, V>::Node* BST<K, V>::put(Node *troot, const K &key, const V &val)
{
    if (troot == nullptr) return new Node(key, val);
    if (troot->key == key) *(troot->val) = val;
    else if (troot->key < key) troot->right = put(troot->right, key, val);
    else troot->left = put(troot->left, key, val);
    troot->size = size(troot->left) + size(troot->right) + 1;
    return troot;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::floor(Node *troot, const K &key)
{
    if (troot == nullptr) return nullptr;
    if (troot->key == key) return troot;
    if (troot->key < key) {
        Node* p = floor(troot->right, key);
        return p == nullptr ? troot : p;
    }
    return floor(troot->left, key);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::ceil(Node *troot, const K &key)
{
    if (troot == nullptr) return nullptr;
    if (troot->key == key) return troot;
    if (troot->key < key) return ceil(troot->right, key);
    Node *p = floor(troot->left, key);
    return p == nullptr ? troot : p;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::select(Node *troot, int i)
{
    if (troot == nullptr || i < 0 ||  i >= size()) return nullptr;
    int left_size = size(troot->left);
    if (left_size == i) return troot;
    if (left_size < i) return select(troot->right, i-left_size-1);
    return select(troot->left, i);
}

template <typename K, typename V>
int BST<K, V>::rank(const Node *troot, const K &key)
{
    if (troot == nullptr) return 0;
    if (troot->key == key) return size(troot->left);
    if (troot->key < key) return size(troot->left) + 1 + rank(troot->right, key);
    return rank(troot->left, key);
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::delete_min(Node *troot)
{
    if (troot == nullptr) return nullptr;
    if (troot->left == nullptr) {
        Node *r = troot->right;
        delete troot;
        return r;
    }
    troot->left = delete_min(troot->left);
    troot->size = size(troot->left) + size(troot->right) + 1;
    return troot;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::delete_max(Node *troot)
{
    if (troot == nullptr) return nullptr;
    if (troot->right == nullptr) {
        Node *l = troot->left;
        delete troot;
        return l;
    }
    troot->right = delete_max(troot->right);
    troot->size = size(troot->left) + size(troot->right) + 1;
    return troot;
}

template <typename K, typename V>
typename BST<K, V>::Node* BST<K, V>::ddelete(Node *troot, const K &key)
{
    if (troot == nullptr) return nullptr;
    if (troot->key == key) {
        // 如果是最大或最小节点, 就直接删除
        if (troot->left == nullptr) {
            Node *p = troot->right;
            delete troot;
            return p;
        }
        if (troot->right == nullptr) {
            Node *p = troot->left;
            delete troot;
            return p;
        }
        // 用右子树最小节点替换自己
        Node *p = min(troot->right);
        Node *new_node = new Node(p->key, *(p->val), p->size);
        new_node->left = troot->left;
        new_node->right = delete_min(troot->right);
        delete troot;
        troot = new_node;
    }
    else if (troot->key < key) troot->right = ddelete(troot->right, key);
    else troot->left = ddelete(troot->left, key);
    troot->size = size(troot->left) + size(troot->right) + 1;
    return troot;
}

template <typename K, typename V>
void BST<K, V>::keys(const Node* troot, vector<K> &ks, const K &lo, const K &hi)
{
    if (troot == nullptr) return;
    // 中序遍历
    if (lo < troot->key) keys(troot->left, ks, lo, hi);
    if (lo <= troot->key && troot->key <= hi) ks.push_back(troot->key);
    if (troot->key < hi) keys(troot->right, ks, lo, hi);
}

#endif // BST_H_INCLUDED

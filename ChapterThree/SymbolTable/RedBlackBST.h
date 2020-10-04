#ifndef REDBLACKBST_H_INCLUDED
#define REDBLACKBST_H_INCLUDED

#include <vector>
// 2020-10-03-23.34
// 算法3.4 红黑树


template <typename K, typename V>
class RedBlackBST {
private:
    static constexpr bool RED = true;
    static constexpr bool BLACK = false;
    struct Node {
        K key;
        V *val;
        Node *left;
        Node *right;
        int size;
        bool color;
        Node(const K &k, const V &v, int n=1, Node *l=nullptr, Node *r=nullptr, bool clr=RED):
            key(k), left(l), right(r), size(n), color(clr)
            { val = new V(v); }
        ~Node() { delete val; }
    };
    Node *root;

public:
    RedBlackBST(): root(nullptr) {}
    ~RedBlackBST() { clear(root); }
    // TODO 拷贝构造函数 和 赋值运算符重载函数

    bool contains(const K &key) { return get(key) != nullptr; }
    int empty() { return size(root) == 0; }
    int size() { return size(root); }

    // 红黑树只有 put delete_min delete_max ddelete 与 二叉查找树实现不同
    V* get(const K &key) { return get(root, key); }
    void put(const K &key, const V &val) {
        root = put(root, key, val);
        root->color = BLACK; // 根节点始终是黑色
    }

    void delete_min();
    void delete_max();
    void ddelete(const K &key);

    // 这些函数都可能会出错 访问空指针
    K min() { return min(root)->key; }
    K max() { return max(root)->key; }
    K floor(const K &key) { return floor(root, key)->key; }
    K ceil(const K &key) { return ceil(root, key)->key; }
    K select(int i) { return select(root, i)->key; }

    int rank(const K &key) { return rank(root, key); }
    std::vector<K> keys() { return keys(min(), max()); }
    std::vector<K> keys(const K &lo, const K &hi) {
        std::vector<K> ks;
        keys(root, ks, lo, hi);
        return ks;
    }


private:
    bool isred(Node *troot) { return troot != nullptr && troot->color == RED;}
    // 红黑树三种操作
    Node* rotate_left(Node *troot);
    Node* rotate_right(Node *troot);
    void flip_colors(Node *troot);

    V* get(const Node *troot, const K &key);
    Node* put(Node *troot, const K &key, const V &val);
    Node* move_red_left(Node *troot);
    Node* move_red_right(Node *troot);
    Node* balance(Node *troot);
    Node* delete_min(Node *troot);
    Node* delete_max(Node *troot);
    Node* ddelete(Node *troot, const K &key);

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
    void keys(const Node* troot, std::vector<K> &ks, const K &lo, const K &hi);
};

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::rotate_left(Node *troot)
{
    Node *right = troot->right;
    troot->right = right->left;
    right->left = troot;
    right->color = troot->color;
    troot->color = RED;
    right->size = troot->size;
    troot->size = 1 + size(troot->left) + size(troot->right);
    return right;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::rotate_right(Node *troot)
{
    Node *left = troot->left;
    troot->left = left->right;
    left->right = troot;
    left->color = troot->color;
    troot->color = RED;
    left->size = troot->size;
    troot->size = 1 + size(troot->left) + size(troot->right);
    return left;
}

template <typename K, typename V>
void RedBlackBST<K, V>::flip_colors(Node *troot)
{
    troot->color = RED;
    troot->left->color = BLACK;
    troot->right->color = BLACK;
}

template <typename K, typename V>
V* RedBlackBST<K, V>::get(const Node* troot, const K &key)
{
    if (troot == nullptr) return nullptr;
    if (troot->key == key) return troot->val;
    if (troot->key < key) return get(troot->right, key);
    return get(troot->left, key);
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::put(Node *troot, const K &key, const V &val)
{
    if (troot == nullptr) return new Node(key, val);
    if (troot->key == key) *(troot->val) = val;
    else if (troot->key < key) troot->right = put(troot->right, key, val);
    else troot->left = put(troot->left, key, val);

    if (!isred(troot->left) && isred(troot->right)) troot = rotate_left(troot);
    if (isred(troot->left) && isred(troot->left->left)) troot = rotate_right(troot);
    if (isred(troot->left) && isred(troot->right)) flip_colors(troot);
    troot->size = size(troot->left) + size(troot->right) + 1;
    return troot;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::move_red_left(Node *troot)
{
    troot->color = BLACK;
    troot->left->color = RED;
    troot->right->color = RED;
    if (isred(troot->right->left)) {
        troot->right = rotate_right(troot->right);
        troot = rotate_left(troot);
    }
    return troot;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::balance(Node *troot)
{
    if (isred(troot->right)) troot = rotate_left(troot);
    if (!isred(troot->left) && isred(troot->right)) troot = rotate_left(troot);
    if (isred(troot->left) && isred(troot->left->left)) troot = rotate_right(troot);
    if (isred(troot->left) && isred(troot->right)) flip_colors(troot);
    troot->size = size(troot->left) + size(troot->right) + 1;
    return troot;
}

template <typename K, typename V>
void RedBlackBST<K, V>::delete_min()
{
    if (!isred(root->left) && isred(root->right))
        root->color = RED;
    root = delete_min(root);
    if (root != nullptr) root->color = BLACK;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::delete_min(Node *troot)
{
    if (troot->left == nullptr) {
        delete troot;
        return nullptr;
    }
    if (!isred(troot->left) && !isred(troot->left->left))
        troot = move_red_left(troot);
    troot->left = delete_min(troot->left);
    return balance(troot);
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::move_red_right(Node *troot)
{
    troot->color = BLACK;
    troot->left->color = RED;
    troot->right->color = RED;
    if (!isred(troot->left->left))
        troot = rotate_right(troot);
    return troot;
}

template <typename K, typename V>
void RedBlackBST<K, V>::delete_max()
{
    if (!isred(root->left) && isred(root->right))
        root->color = RED;
    root = delete_max(root);
    if (root != nullptr) root->color = BLACK;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::delete_max(Node *troot)
{
    if (isred(troot->left))
        troot = rotate_right(troot);
    if (troot->right == nullptr) {
        delete troot;
        return nullptr;
    }
    if (!isred(troot->right) && isred(troot->right->left))
        troot = move_red_right(troot);
    troot->right = delete_max(troot->right);
    return balance(troot);
}

template <typename K, typename V>
void RedBlackBST<K, V>::ddelete(const K &key)
{
    if (!isred(root->left) && isred(root->right))
        root->color = RED;
    root = ddelete(root, key);
    if (root != nullptr) root->color = BLACK;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::ddelete(Node *troot, const K &key)
{
    if (troot->key <= key) {
        if (isred(troot->left))
            troot= rotate_right(troot);
        if (troot->key == key && troot->right == nullptr) {
            delete troot;
            return nullptr;
        }
        if (!isred(troot->right) && !isred(troot->right->left))
            troot = move_red_right(troot);
        if (troot->key == key) {
            Node* min_node = min(troot->right);
            *(troot->val) = *(get(troot->right, min_node->key));
            troot->key = min_node->key;
            troot->right = delete_min(troot->right);
        }
        else troot->right = ddelete(troot->right, key);
    }
    else {
        if (!isred(troot->left) && !isred(troot->left->left))
            troot = move_red_left(troot);
        troot->left = ddelete(troot->left, key);
    }
    return balance(troot);
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::floor(Node *troot, const K &key)
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
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::ceil(Node *troot, const K &key)
{
    if (troot == nullptr) return nullptr;
    if (troot->key == key) return troot;
    if (troot->key < key) return ceil(troot->right, key);
    Node *p = floor(troot->left, key);
    return p == nullptr ? troot : p;
}

template <typename K, typename V>
typename RedBlackBST<K, V>::Node* RedBlackBST<K, V>::select(Node *troot, int i)
{
    if (troot == nullptr || i < 0 ||  i >= size()) return nullptr;
    int left_size = size(troot->left);
    if (left_size == i) return troot;
    if (left_size < i) return select(troot->right, i-left_size-1);
    return select(troot->left, i);
}

template <typename K, typename V>
int RedBlackBST<K, V>::rank(const Node *troot, const K &key)
{
    if (troot == nullptr) return 0;
    if (troot->key == key) return size(troot->left);
    if (troot->key < key) return size(troot->left) + 1 + rank(troot->right, key);
    return rank(troot->left, key);
}

template <typename K, typename V>
void RedBlackBST<K, V>::keys(const Node* troot, std::vector<K> &ks, const K &lo, const K &hi)
{
    if (troot == nullptr) return;
    // 中序遍历
    if (lo < troot->key) keys(troot->left, ks, lo, hi);
    if (lo <= troot->key && troot->key <= hi) ks.push_back(troot->key);
    if (troot->key < hi) keys(troot->right, ks, lo, hi);
}
#endif // REDBLACKBST_H_INCLUDED

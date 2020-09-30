#ifndef SEQUENTIALSEARCHST_H_INCLUDED
#define SEQUENTIALSEARCHST_H_INCLUDED

#include <set>
// 2020-09-29-20.54
// 算法 3.1 无序链表

template <typename K, typename V>
class SequentialSearchST {
    struct Node {
        K key;
        V *val;
        Node *next;
        Node(const K &k, const V &v, Node *n): key(k), next(n) { val = new V(v);}
        ~Node() { if (val != nullptr) delete val; }
    };
    Node *first_;
    int size_;
    std::set<K> keys_;

public:
    SequentialSearchST(): first_(nullptr), size_(0) {}
    ~SequentialSearchST() { clear(); }

    // TODO 拷贝构造函数 赋值运算符重载函数

    void put(const K &key, const V &val) {
        for (Node *pos = first_; pos != nullptr; pos = pos->next) {
            if (key == pos->key) {
                if (pos->val == nullptr) {
                    pos->val = new V(val);
                    size_++;
                    keys_.insert(key);
                    return;
                }
                // 已经存在 进行更新
                *(pos->val) = val;
                return;
            }
        }
        first_ = new Node(key, val, first_);
        size_++;
        keys_.insert(key);
    }

    // 返回 nullptr 即表中不存在
    V* get(const K &key) {
        for (Node *pos = first_; pos != nullptr; pos = pos->next) {
            if (key == pos->key) return pos->val;
        }
        return nullptr;
    }

    // 延迟删除
    void ddelete(const K &key) {
        for (Node *pos = first_; pos != nullptr; pos = pos->next) {
            if (key == pos->key) {
                delete pos->val;
                pos->val = nullptr;
                size_--;
                keys_.erase(key);
            }
        }
    }


    bool contains(const K &key) { return get(key) != nullptr; }
    bool empty() { return size_ == 0; }
    int size() { return size_; }
    std::set<K> keys() { return keys_; }

private:
    void clear();
};

template <typename K, typename V>
void SequentialSearchST<K,V>::clear()
{
    Node *next;
    while (first_ != nullptr) {
        next = first_->next;
        delete first_;
        first_ = next;
    }
    size_ = 0;
}

#endif // SEQUENTIALSEARCHST_H_INCLUDED

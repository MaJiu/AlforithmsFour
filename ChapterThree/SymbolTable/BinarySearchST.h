#ifndef BINARYSEARCHST_H_INCLUDED
#define BINARYSEARCHST_H_INCLUDED
#include <vector>
// 2020-09-30-17.04
// 算法 3.2 二分查找
// 有序数组 没有重复元素

template <typename K, typename V>
class BinarySearchST {
    K *keys_;
    V *vals_;
    int capacity_;
    int size_;

public:
    explicit BinarySearchST(int capacity = 20): capacity_(capacity), size_(0) {
        keys_ = new K[capacity];
        vals_ = new V[capacity];
    }
    ~BinarySearchST() {
        delete[] keys_;
        delete[] vals_;
    }
    // TODO 拷贝构造函数 赋值运算符重载函数

    V* get(const K &key);
    void put(const K &key, const V &val);
    void ddelete(const K &key);

    // 小于 key 的键的数量
    // 大于等于 key 的键最小下标
    // 如果 key 存在就是 key 的位置, 如果 key 不存在就是 key应该插入的位置
    // lower_bound
    int rank(const K &key);

    // 大于等于 key 的键
    K ceil(const K &key) {
        return keys_[rank(key)];
    }

    // 小于等于 key 的键
    K floor(const K &key) {

    }

    // 最小的键
    K min() { return keys_[0]; }

    // 最大的键
    K max() { return keys_[size_-1]; }

    // 排名为 k 的键
    K select(int k) { return keys_[k]; }
    bool contains(const K &key) { return get(key) != nullptr; }
    int empty() { return size_ == 0; }
    int size() { return size_; }
    std::vector<K> keys() { return std::vector<K>(keys_, keys_+size_); }
private:
    void resize(int new_capacity);
};

template <typename K, typename V>
void BinarySearchST<K,V>::resize(int new_capacity)
{
    capacity_ = new_capacity;
    K *new_keys = new K[new_capacity];
    V *new_vals = new V[new_capacity];
    for (int i=0; i<size_; i++) {
        new_keys[i] = keys_[i];
        new_vals[i] = vals_[i];
    }
    delete[] keys_;
    delete[] vals_;
    keys_ = new_keys;
    vals_ = new_vals;
}

template <typename K, typename V>
V* BinarySearchST<K, V>::get(const K &key)
{
    if (empty()) return nullptr;
    int i = rank(key);
    return (i < size_ && keys_[i] == key) ? vals_+i : nullptr;
}

template <typename K, typename V>
void BinarySearchST<K, V>::put(const K &key, const V &val)
{
    int i = rank(key);
    if (i < size_ && keys_[i] == key) {
        // 已经存在 进行更新
        vals_[i] = val;
        return;
    }
    if (size_ == capacity_) resize(capacity_*2);
    for (int j = size_; j > i; j--) {
        keys_[j] = keys_[j-1];
        vals_[j] = vals_[j-1];
    }
    keys_[i] = key;
    vals_[i] = val;
    size_++;
}

template <typename K, typename V>
void BinarySearchST<K, V>::ddelete(const K & key)
{
    if (empty()) return;
    int i = rank(key);
    if (i >= size_ || keys_[i] != key) return;
    for (int j=i; j<size_-1; j++) {
        keys_[i] = keys_[i+1];
        vals_[i] = vals_[i+1];
    }
    size_--;
    if ( 0 < size_ && size_ == capacity_ / 4) resize(capacity_ / 2);
}

template <typename K, typename V>
int BinarySearchST<K, V>::rank(const K &key)
{
    int l = 0;
    int r = size_-1; // 闭区间
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (key < keys_[mid]) r = mid - 1;
        else if (key == keys_[mid]) return mid;
        else l = mid + 1;
    }
    return l;
}
#endif // BINARYSEARCHST_H_INCLUDED

#ifndef LINEARPROBINGHASHST_H_INCLUDED
#define LINEARPROBINGHASHST_H_INCLUDED

#include <functional>
#include <set>

template <typename K, typename V>
class LinearProbingHashST {
private:
    int size_;
    int m_;
    /*
    * 这里如果使用 K *keys_; V *vals_;
    * 后续 keys_ = new K[m_]; new 出一个数组时, 数组元素会调用默认构造函数(内置类型不会初始化),
    * 判断一个 key 在不在 keys_ 时会发生混淆, 有可能新插入一个键 key 时,
    * keys[hash(key)] 恰好等于 key, 这种情况在当 V 是内置类型的时候更有可能发生,
    * 未经初始化的 keys[hash(key)] 恰好等于 新插入的键 key
    */
    K **keys_;
    V **vals_;
    std::hash<K> hash_of_key;
    std::set<K> ks;
public:
    LinearProbingHashST(int capacity = 16): size_(0), m_(capacity) {
        keys_ = new K*[m_]();
        vals_ = new V*[m_]();
    }

    ~LinearProbingHashST() {
        for (int i=0; i<m_; i++) {
            if (keys_[i]) delete keys_[i];
            if (vals_[i]) delete vals_[i];
        }
        delete[] keys_;
        delete[] vals_;
    }

    // TODO 拷贝构造函数 赋值运算符重载函数
    V* get(const K &key);
    void put(const K &key, const V &val);
    void ddelete(const K &key);

    bool contains(const K &key) { return get(key) != nullptr; }
    int size() {return size_;}
    bool empty() { return size_ == 0;}

    std::set<K> keys() {
        return ks;
    }

private:
    int hash(const K &key) {return hash_of_key(key) % m_;}
    // ddelete 专用
    void put(K *pkey, V *pval);
    // resize 专用
    void put(K &&key, V &&val);
    void resize(int cap);
};


template <typename K, typename V>
V* LinearProbingHashST<K, V>::get(const K &key)
{
    for (int i=hash(key); keys_[i] != nullptr; i = (i + 1) % m_) {
        if (*(keys_[i]) == key) return vals_[i];
    }
    return nullptr;
}

template <typename K, typename V>
void LinearProbingHashST<K, V>::put(const K &key, const V &val)
{
    if (size_ >= m_/2) resize(2*m_);
    int i = hash(key);
    for (; keys_[i] != nullptr;  i = (i + 1) % m_) {
        if (*(keys_[i]) != key) continue;
        *(vals_[i]) = val;
        return;
    }
    keys_[i] = new K(key);
    vals_[i] = new V(val);
    ks.insert(*(keys_[i]));
    size_++;
}


template <typename K, typename V>
void LinearProbingHashST<K, V>::put(K &&key, V &&val)
{
    if (size_ >= m_/2) resize(2*m_);
    int i = hash(key);
    for (; keys_[i] != nullptr;  i = (i + 1) % m_) {
        if (*(keys_[i]) != key) continue;
        *(vals_[i]) = val;
        return;
    }
    keys_[i] = new K(key);
    vals_[i] = new V(val);
    ks.insert(key);
    size_++;
}

// 内部调整使用 调整 (key, val) 的位置
template <typename K, typename V>
void LinearProbingHashST<K, V>::put(K* pkey, V *pval)
{
    int i = hash(*pkey);
    while (keys_[i] != nullptr) i = (i + 1) % m_;
    keys_[i] = pkey;
    vals_[i] = pval;
}


template <typename K, typename V>
void LinearProbingHashST<K, V>::ddelete(const K &key)
{
    if (!contains(key)) return;
    int i = hash(key);
    while (*(keys_[i]) != key) i = (i + 1) % m_;
    ks.erase(*(keys_[i]));
    delete keys_[i];
    delete vals_[i];
    keys_[i] = nullptr;
    vals_[i] = nullptr;
    i = (i + 1) % m_;
    size_--;
    while (keys_[i] != nullptr) {
        K *key_to_redo = keys_[i];
        V *val_to_redo = vals_[i];
        keys_[i] = nullptr;
        vals_[i] = nullptr;
        put(key_to_redo, val_to_redo);
        i = (i + 1) % m_;
    }
    if (size_ > 0 && size_ == m_ / 8) resize(m_/2);
}

template <typename K, typename V>
void LinearProbingHashST<K, V>::resize(int cap)
{
    LinearProbingHashST<K, V> t(cap);
    for (int i=0; i < m_; i++) {
        if (keys_[i] != nullptr) t.put(std::move(*(keys_[i])), std::move(*(vals_[i]))); // 可以考虑使用 move
    }
    // 两个进行交换 resize 执行完后, t 会被销毁, 执行析构函数 不会发生内存泄漏
    std::swap(keys_, t.keys_);
    std::swap(vals_, t.vals_);
    std::swap(m_, t.m_);
}
#endif // LINEARPROBINGHASHST_H_INCLUDED

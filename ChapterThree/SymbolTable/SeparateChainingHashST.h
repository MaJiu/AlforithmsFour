#ifndef SEPARATECHAININGHASHST_H_INCLUDED
#define SEPARATECHAININGHASHST_H_INCLUDED

#include <functional>
#include <vector>
#include "SequentialSearchST.h"


template <typename K, typename V>
class SeparateChainingHashST {
private:
    int size_;
    int m_;
    SequentialSearchST<K, V> *st;
    std::hash<K> hash_of_key;
public:
    SeparateChainingHashST(int m=997): size_(0), m_(m) {
        st = new SequentialSearchST<K, V>[m];
    }
    ~SeparateChainingHashST() { delete[] st;}
    V* get(const K &key) { return st[hash(key)].get(key); }
    void put(const K &key, const V &val) {
        if (!contains(key)) size_++;
        st[hash(key)].put(key, val);
    }
    void ddelete(const K &key) {
        if (!contains(key)) return;
        st[hash(key)].ddelete(key);
        size_--;
    }
    bool contains(const K &key) { return st[hash(key)].contains(key); }
    int size() {return size_;}
    bool empty() { return size_ == 0;}
    std::vector<K> keys() {
        vector<K> ks;
        for (int i=0; i<m_; i++) {
            if (st[i].empty()) continue;
            auto st_keys = st[i].keys();
            ks.insert(ks.end(), st_keys.begin(), st_keys.end());
        }
        return ks;
    }

private:
    int hash(const K &key) {return hash_of_key(key) % m_;}
};

#endif // SEPARATECHAININGHASHST_H_INCLUDED

#ifndef BAG_H_INCLUDED
#define BAG_H_INCLUDED

// 算法1.4 背包
template <typename T>
class Bag {
    struct Node {
        T item;
        Node *next;
        Node(): next(nullptr) {};
    };
    Node *first_;
    //迭代器
public:
    class iterator {
        Node *p_;
    public:
        iterator(): p_(nullptr) {}
        iterator(Node *ptr): p_(ptr) {}
        T& operator*() const { return p_->item; }
        bool operator!=(const iterator &rhs) const { return p_ != rhs.p_; }
        iterator& operator++() {
            if (p_ != nullptr) p_ = p_->next;
            return *this;
        }
    };

public:
    Bag(): first_(nullptr) {}
    Bag(const Bag &another);
    Bag& operator=(const Bag &another);
    ~Bag() { clear(); }

    void add(const T &item);
    iterator begin() {return iterator(first_); }
    iterator end() { return iterator(); }

private:
    void clear();
};

template <typename T>
void Bag<T>::clear()
{
    Node *next;
    while (first_ != nullptr) {
        next = first_->next;
        delete first_;
        first_ = next;
    }
}

template <typename T>
Bag<T>::Bag(const Bag<T> &another)
{
    if (another->first_ == nullptr) return;
    first_ = new Node();
    first_->item = another.first_->item;
    Node *another_cur = another.first_->next;
    Node *this_cur = first_;
    while (another_cur != nullptr) {
        this_cur->next = new Node();
        this_cur->next->item = another_cur->item;
        this_cur = this_cur->next;
        another_cur = another_cur->next;
    }

}

template <typename T>
Bag<T>& Bag<T>::operator=(const Bag<T> &rhs)
{
    clear();
    if (rhs.empty()) return *this;
    first_ = new Node();
    first_->item = rhs.first_->item;
    Node *rhs_cur = rhs.first_->next;
    Node *this_cur = first_;
    while (rhs_cur != nullptr) {
        this_cur->next = new Node();
        this_cur->next->item = rhs_cur->item;
        this_cur = this_cur->next;
        rhs_cur = rhs_cur->next;
    }
    return *this;
}

template <typename T>
void Bag<T>::add(const T &item)
{
    Node *old_first = first_;
    first_ = new Node();
    first_->item = item;
    first_->next = old_first;
}
#endif // BAG_H_INCLUDED

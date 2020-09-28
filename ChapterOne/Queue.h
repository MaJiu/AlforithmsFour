#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED


// 算法 1.3
// 队列
template <typename T>
class Queue {
    struct Node {
        T item;
        Node *next;
        Node(): next(nullptr) {};
    };
    Node *first_;
    Node *last_;
    int n_;

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
    Queue(): first_(nullptr), last_(nullptr), n_(0) {}
    Queue(const Queue &another);
    Queue& operator=(const Queue &rhs);
    ~Queue() { clear(); }
    bool empty() const { return n_ == 0; }
    int size() const { return n_; }
    void enqueue(const T &item);
    T dequeue();
    iterator begin() {return iterator(first_); }
    iterator end() { return iterator(); }
private:
    void clear();
};

template <typename T>
void Queue<T>::clear()
{
    if (empty()) return;
    Node *cur = first_;
    Node *next = cur->next;
    while (cur) {
        next = cur->next;
        delete cur;
        cur = next;
    }
    first_ = nullptr;
    n_ = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &another)
{
    if (another.empty()) return;
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
    last_ = this_cur;
    n_ = another.n_;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &rhs)
{
    clear(); //清空重新构造
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
    last_ = rhs.last_;
    n_ = rhs.n_;
    return *this;
}

template <typename T>
void Queue<T>::enqueue(const T &item)
{
    Node *old_last = last_;
    last_ = new Node();
    last_->item = item;
    if (empty()) {
        first_ = last_;
    } else old_last->next = last_;
    n_++;
}

template <typename T>
T Queue<T>::dequeue()
{
    T item = first_->item;
    first_ = first_->next;
    if (empty()) last_ = nullptr;
    n_--;
    return item;
}
#endif // QUEUE_H_INCLUDED

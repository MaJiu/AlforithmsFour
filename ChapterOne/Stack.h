#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

// 算法1.2
// 下压栈 链表实现
template <typename T>
class Stack {
private:
    struct Node {
        T item;
        Node *next;
        Node(): next(nullptr) {};
    };
    Node *first_;
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
    Stack(): first_(nullptr), n_(0) {}
    Stack(const Stack &another);
    Stack &operator=(const Stack &rhs);
    ~Stack();

    bool empty() const { return first_ == nullptr;}
    int size() const {return n_;};
    void push(T &item);
    T pop();
    iterator begin() {return iterator(first_); }
    iterator end() { return iterator(); }

private:
    void clear();
};

template <typename T>
void Stack<T>::clear()
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
Stack<T>::Stack(const Stack<T> &another): first_(nullptr), n_(0)
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
    n_ = another.n_;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &rhs)
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
    n_ = rhs.n_;
    return *this;
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
void Stack<T>::push(T &item)
{
    Node *old_first = first_;
    first_ = new Node();
    first_->item = item;
    first_->next = old_first;
    n_++;
}

template <typename T>
T Stack<T>::pop()
{
    T item = first_->item;
    Node *old_first = first_;
    first_ = first_->next;
    delete old_first;
    n_ --;
    return item;
}
#endif // STACK_H_INCLUDED

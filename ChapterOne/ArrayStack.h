#ifndef ARRAYSTACK_H_INCLUDED
#define ARRAYSTACK_H_INCLUDED

// 算法 1.1
// 下压栈能够动态调整数组大小的实现
template <typename T>
class ArrayStack {
    int n_;
    int capacity_;
    T *data_;

public:
    // 实现迭代器
    class iterator {
        T *p_;
    public:
        iterator(): p_(nullptr) {}
        iterator(T *ptr): p_(ptr) {}
        T& operator*() const { return *p_; }
        bool operator!=(const iterator &rhs) const { return p_ != rhs.p_; }
        iterator& operator++() {
            p_--;
            return *this;
        }
    };
public:
    ArrayStack(): n_(0), capacity_(1) {
        data_ = new T[capacity_];
    }
    ArrayStack(const ArrayStack &another);
    ArrayStack& operator=(const ArrayStack &rhs);
    ~ArrayStack() { delete[] data_; n_=0;};

    bool empty() const { return n_ == 0;}
    int size() const { return n_; };
    void push(const T &item);
    T pop();
    // 为支持 范围for 需要添加 begin 和 end
    iterator begin() { return iterator(data_ + n_ - 1); }
    iterator end() { return iterator(data_ - 1); }

private:
    void resize(int max);
};

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T> &another)
{
    data_ = new T[another.capacity_];
    for (int i=0; i<another.capacity_; i++) {
        data_[i] = another.data_[i];
    }
    n_ = another.n_;
    capacity_ = another.capacity_;
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T> &rhs)
{
    delete[] data_;
    data_ = new T[rhs.capacity_];
    for (int i=0; i<rhs.capacity_; i++) {
        data_[i] = rhs.data_[i];
    }
    n_ = rhs.n_;
    capacity_ = rhs.capacity_;
}

template <typename T>
void ArrayStack<T>::resize(int max)
{
    T *new_data = new T[max];
    for (int i=0; i<n_; i++) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
}

template <typename T>
void ArrayStack<T>::push(const T &item)
{
    if (n_ == capacity_) {
        capacity_ *= 2;
        resize(capacity_);
    }
    data_[n_++] = item;
}

template <typename T>
T ArrayStack<T>::pop()
{
    T item = data_[n_--];
    if ( 0 < n_ && n_ == capacity_ / 4) {
        capacity_ /= 2;
        resize(capacity_);
    }
    return item;
}
#endif // ARRAYSTACK_H_INCLUDED

#ifndef ITERATOR_H
#define ITERATOR_H

template <class T>
class Iterator {
public:
    Iterator(T* ptr) : ptr_(ptr) {}

    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_; }

    Iterator& operator++() {
        ptr_++;
        return *this;
    }

    bool operator==(const Iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator& other) const {
        return ptr_ != other.ptr_;
    }

private:
    T* ptr_;
};

#endif // !ITERATOR_H
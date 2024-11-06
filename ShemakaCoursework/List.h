#ifndef LIST_H
#define LIST_H

#include <iostream>

template<typename T>
class List {
public:
    List() : head_(nullptr) {}
    ~List() { clear(); }

    bool insert(const T& newData) {
        if (!head_) {
            head_ = new Node(newData);
            return true;
        }
        Node* cur = head_;
        while (cur->next_ && cur->data_ < newData) {
            cur = cur->next_;
        }
        if (cur->data_ == newData) {
            return false; // Duplicate item
        }
        Node* newNode = new Node(newData);
        newNode->next_ = cur->next_;
        cur->next_ = newNode;
        return true;
    }

    bool search(const T& data) const {
        Node* cur = head_;
        while (cur) {
            if (cur->data_ == data) {
                return true;
            }
            cur = cur->next_;
        }
        return false;
    }

    bool isEmpty() const { return head_ == nullptr; }

    friend std::ostream& operator<<(std::ostream& out, const List& list) {
        Node* cur = list.head_;
        while (cur) {
            out << cur->data_ << ' ';
            cur = cur->next_;
        }
        return out;
    }

private:
    struct Node {
        T data_;
        Node* next_;
        Node(const T& newData) : data_(newData), next_(nullptr) {}
    };

    Node* head_;

    void clear() {
        while (head_) {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }
};

#endif // LIST_H
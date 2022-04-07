#pragma once
#ifndef LINKED_LIST__
#define LINKED_LIST__

#include <iostream>
#include <fstream>
#include <memory>

template<typename T>
class Node {
public:
    Node* next_;
    Node* prev_;
    T data_;

    Node() = default;

    Node(T val): data_{val}, next_{}, prev_{} {};
};

template<typename T>
bool operator==(Node<T> lhs, Node<T> rhs) {
    return lhs.data_ == rhs.data_;
}

template<typename T>
bool operator<=>(Node<T> lhs, Node<T> rhs) {
    return &lhs <=> &rhs;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Node<T> node) {
    return os << "{" << node.data_ << "}";
}

template<typename T>
class LinkedList {
private:
    Node<T>* head_;
    Node<T>* tail_;


    void insert_after_(T&& val, Node<T>& prev) {
        // NOTE: that this make not possible
        // to insert into empty list
        if (prev == nullptr) {
            return;
        }

        const auto& node = std::make_shared<Node<T>>(
                * (new Node{std::move(val)})
        );

        node->next = prev.next_;
        prev.next_ = node;
        node->prev_ = prev;
        if (node->next_ != nullptr) {
            node->next_->prev_ = node;
        }
    }

    Node<T> remove_(Node<T>& node) {
        if (node == nullptr) {
            return;
        }

        if (node->next_ != nullptr) {
            node->next_->prev_ = node->prev_;
        }

        if (node->prev_ != nullptr) {
            node->prev->next = node->next_;
        }

        return node;
    }

    // TODO: bad coupling
    void swap(Node<T>& a, Node<T>& b) {
        std::swap(a.data_, b.data_);
        std::swap(a.prev_, b.prev_);
        std::swap(a.next_, b.next_);
    }

public:

    Node<T>* head() const { return head_; }
    Node<T>* tail() const { return tail_; }

    void push_front(T&& val) {
        const auto& node = new Node{std::move(val)};
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            head_->prev_ = node;
            node->next_ = head_;
            head_ = node;
        }
    }

    void push_back(T&& val) {
        const auto &node = new Node{std::move(val)};

        if (head_ == nullptr) {
            head_ = node;
        }

        if (tail_ != nullptr) {
            tail_->next_ = node;
        }

        node->next_ = nullptr;
        node->prev_ = tail_;
        tail_ = node;
    }

    template<class Compare>
    void sort(Compare comp) {
        if (head_ == nullptr || head_ == tail_) {
            return;
        }

        if (tail_ == nullptr) {
            // TODO: comes from assumption that tail cannot be null, check this
            throw new std::runtime_error("bad linked list passed to sort func");
        }

        auto cur = head_;
        while (cur != nullptr) {
            auto b = cur->next_;
            while (b != nullptr && b->prev_  != nullptr && \
                   comp(b->data_, b->prev_->data_)) {
                   std::swap(b->data_, b->prev_->data_);
                    b = b->prev_;
            }
            cur = cur->next_;
        }
    }

    class LLIterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>>{

    private:
        Node<T>* curr_;

    public:
        LLIterator(Node<T>& node): curr_{node} {}

        Node<T> operator*() const {
            return *curr_;
        }

        LLIterator& operator++() {
            if (curr_) curr_ = curr_->next_;
            return *this;
        }

        LLIterator operator++(int) {
            if (curr_)
                return LLIterator{curr_->next};
            return nullptr;
        }

        LLIterator& operator--() {
            if (curr_) curr_ = curr_->prev;
            return *this;
        }

        LLIterator operator--(int) {
            if (curr_)
                return LLIterator{curr_->prev};
            return nullptr;
        }

        LLIterator& operator=(Node<T>& node) {
            curr_ = node;
            return *this;
        }

        // TODO: slightly awkward code, think more on it
        bool operator!=(const LLIterator& it) {
            auto other_curr = it.curr_;
            if (other_curr == nullptr && curr_ == nullptr) {
                return false;
            } else if (other_curr == nullptr || curr_ == nullptr) {
                return true;
            }

            return other_curr == curr_;
        }
    };

    LLIterator begin() {
        return LLIterator{head_};
    }

    LLIterator end() {
        return LLIterator{nullptr};
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, LinkedList<T> ll) {
    auto current = ll.head();
    while (current != nullptr) {
        os << *current;
        current = current->next_;
        if (current != nullptr) os << " -> ";
    }

    return os;
}

#endif // LINKED_LIST__

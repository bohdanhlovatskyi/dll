#pragma once
#ifndef LINKED_LIST__
#define LINKED_LIST__

#include <iostream>
#include <fstream>
#include <memory>
#include <iterator>

template<typename T>
class Node {
public:
    Node* next_;
    Node* prev_;
    T data_;

    Node() = default;
    ~Node() = default;

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

    void insert_after_(T&& val, Node<T>* prev) {
        // NOTE: that this make not possible
        // to insert into empty list
        if (prev == nullptr) {
            return;
        }

        const auto& node = new Node{std::move(val)};

        node->next_ = prev->next_;
        prev->next_ = node;
        node->prev_ = prev;
        if (node->next_ != nullptr) {
            node->next_->prev_ = node;
        }
    }

    Node<T> remove_(Node<T>* node) {
        if (node == nullptr) {
            throw std::runtime_error("could not remove nullptr node");
        }

        if (node->next_ != nullptr) {
            node->next_->prev_ = node->prev_;
        }

        if (node->prev_ != nullptr) {
            node->prev_->next_ = node->next_;
        }

        auto rtn = *node;
        // TODO: memory leak here

        return rtn;
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

    template<class Arg>
    void insert(Arg&& val, size_t pos) {
        if (pos == 0) {
            push_front(std::forward<Arg>(val));
            return;
        }
        auto it = this->begin();
        std::advance(it, pos - 1);

        insert_after_(std::forward<Arg>(val), *it);
    }

    Node<T> remove(size_t pos) {
        auto it = this->begin();
        std::advance(it, pos);

        return remove_(*it);
    }

    template<class Callable>
    Node<T> remove_if(Callable call) {
        auto it = std::find_if(this->begin(), this->end(), call);
        return remove_(*it);
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
                   comp(b->data_, b->prev_->data_))
            {
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
        LLIterator(Node<T>* node): curr_{node} {}

        Node<T>* operator*() {
            return curr_;
        }

        LLIterator& operator++() {
            if (curr_) curr_ = curr_->next_;
            return *this;
        }

        LLIterator operator++(int) {
            if (curr_)
                return LLIterator{curr_->next_};
            return nullptr;
        }

        LLIterator& operator--() {
            if (curr_) curr_ = curr_->prev_;
            return *this;
        }

        LLIterator operator--(int) {
            if (curr_)
                return LLIterator{curr_->prev_};
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

    LLIterator begin() const {
        return LLIterator{head_};
    }

    LLIterator end() const {
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

#pragma once
#ifndef LINKED_LIST__
#define LINKED_LIST__

#include <iostream>
#include <fstream>
#include <memory>

template<typename T>
class Node {
public:
    std::shared_ptr<Node> next_;
    std::shared_ptr<Node> prev_;
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
    return lhs.data_ <=> rhs.data_;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Node<T> node) {
    return os << "{" << node.data_ << "}";
}

template<typename T>
class LinkedList {
private:
    std::shared_ptr<Node<T>> head_;
    std::shared_ptr<Node<T>> tail_;


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

    // TODO: not sure that this is located in right place
    // bad coupling
    void swap(Node<T>& a, Node<T>& b) {
        std::swap(a.data_, b.data_);
        std::swap(a.next_, b.next_);
        std::swap(a.prev_, b.prev_);
    }

    template<class Comparer>
    void helper_(Node<T>& head_, Node<T>& tail_, Comparer comp)
    {
        if (head_ == tail_) {
            return;
        }

        auto& pivot = tail_;
        auto& cur = head_;

        while (*cur.next_ != pivot) {
            // TODO: not sure that it should be > 0 here
            if (comp(cur.data_, pivot.data_) > 0) {
                swap(*pivot.prev_,  pivot);
                swap(pivot, cur);
                pivot = *pivot.prev_;
            } else {
                cur = *cur.next_;
            }
        }

        if (comp(cur.data_, pivot.data_) > 0) {
            swap(cur,  pivot);
            pivot = cur;
        }

        if (head_ != pivot) {
            helper_(head_, *pivot.prev_, comp);
        }

        if (tail_ != pivot) {
            helper_(*pivot.next_,  tail_, comp);
        }
    }

public:

    std::shared_ptr<Node<T>> head() const { return head_; }
    std::shared_ptr<Node<T>> tail() const { return tail_; }

    void push_front(T&& val) {
        const auto& node = std::make_shared<Node<T>>(
                * (new Node{std::move(val)})
                );
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
        const auto &node = std::make_shared<Node<T>>(
                *(new Node{std::move(val)})
        );

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
        if (head_ == tail_) {
            return;
        }

        if (head_ == nullptr || tail_ == nullptr) {
            throw new std::runtime_error("bad linked list passed to sort func");
        }

        helper_(*head_, *tail_, comp);
    }

    class LLIterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>>{

    private:
        std::shared_ptr<Node<T>> curr_;

    public:
        LLIterator(std::shared_ptr<Node<T>> node): curr_{node} {}

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

        LLIterator& operator=(std::shared_ptr<Node<T>> node) {
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

            return other_curr.get() == curr_.get();
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
        os << *current.get();
        current = current.get()->next_;
        if (current != nullptr) os << " -> ";
    }

    return os;
}

#endif // LINKED_LIST__

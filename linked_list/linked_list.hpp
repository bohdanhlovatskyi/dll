#pragma once
#ifndef LINKED_LIST__
#define LINKED_LIST__

#include <iostream>
#include <fstream>
#include <memory>

template<typename T>
class Node {
public:
    std::shared_ptr<Node> next_ = nullptr;
    std::weak_ptr<Node> prev_;
    T data_;

    Node(): data_{} {};

    Node(T val): data_{val} {};
};

template<typename T>
bool operator==(Node<T> lhs, Node<T> rhs) {
    return lhs.data_ == rhs.data_;
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
public:

    // forward declaration of iterator class
    class Iterator;

    // TODO: why does this not work
    // LinkedList(): head_{new Node<T>{}}, tail_{new Node<T>{}} {}

    std::shared_ptr<Node<T>> head() const { return head_; }
    std::shared_ptr<Node<T>> tail() const { return tail_; }

    // TODO: &&
    void push_front(T val) {
        // TODO: where is it located
        const auto node = std::make_shared<Node<T>>(Node{val});
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
        } else {
            head_->prev_ = node;
            node->next_ = head_;
            head_ = node;
        }
    }

    class LLIterator : public std::iterator<std::input_iterator_tag, Node<T>>{
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

        Iterator& operator=(std::shared_ptr<Node<T>> node) {
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

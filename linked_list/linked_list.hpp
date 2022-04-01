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
std::ostream& operator<<(std::ostream& os, Node<T> node) {
    return os << "{" << node.data_ << "}";
}

template<typename T>
class LinkedList {
private:
    std::shared_ptr<Node<T>> head_;
    std::shared_ptr<Node<T>> tail_;
public:

    // TODO: why does this not work
    // LinkedList(): head_{new Node<T>{}}, tail_{new Node<T>{}} {}

    std::shared_ptr<Node<T>> head() { return head_; }
    std::shared_ptr<Node<T>> tail() { return tail_; }

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

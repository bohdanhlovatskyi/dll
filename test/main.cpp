#include <iostream>
#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

#include "../linked_list/linked_list.hpp"

TEST(TestLinkedList, TestInsert) {
    LinkedList<int> ll{};
    ll.push_front(3);
    ll.push_back(4);
    ll.insert(2, 1);
    auto node = ll.remove(1);
    ASSERT_EQ(2, node.data_);
}

TEST(TestLinkedList, TestRemoveIf) {
    LinkedList<int> ll{};
    ll.push_front(3);
    ll.push_back(4);
    ll.insert(2, 1);
    auto node = ll.remove_if([](const auto& elm){ return elm->data_ == 2; });
    ASSERT_EQ(2, node.data_);
}

TEST(TestLinkedList, TestSort) {
    LinkedList<int> ll{};
    ll.push_front(7);
    ll.push_back(4);
    ll.push_back(9);
    ll.sort([](const auto& a, const auto& b){ return a < b; });

    std::vector<int> a;
    for (const auto& node : ll) {
        a.push_back(node->data_);
    }

    std::vector<int> b = {4, 7, 9};
    ASSERT_EQ(b, a);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

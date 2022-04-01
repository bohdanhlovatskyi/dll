#include <iostream>
#include <algorithm>

#include "gtest/gtest.h"

#include "../linked_list/linked_list.hpp"

TEST(TestLinkedList, TestFind) {
    LinkedList<int> ll{};
    ll.push_front(3);
    ll.push_front(5);
    ll.push_front(2);

    ASSERT_EQ(*std::find(ll.begin(), ll.end(), 3), 3);
    ASSERT_EQ(*std::find(ll.begin(), ll.end(), 5), 5);
    ASSERT_EQ(*std::find(ll.begin(), ll.end(), 2), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

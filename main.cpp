// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <algorithm>

#include <linked_list.hpp>

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;


    Node<int> n{5};

    LinkedList<int> a{};
    a.push_front(7);
    a.push_front(3);
    a.push_front(5);
    a.push_front(1);

    std::cout << a << std::endl;

    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    auto res = std::find(a.begin(), a.end(), 5);
    std::cout << *res << std::endl;

    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << ", ";
    }

    return 0;
}

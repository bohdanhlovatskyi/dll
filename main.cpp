// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <vector>

#include <linked_list.hpp>

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;


    Node<int> n{5};

    LinkedList<int> a{};
    a.push_front(5);
    a.push_front(3);
    a.push_front(7);
    a.push_front(13);

    std::cout << a << std::endl;

    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << ", ";
    }

    return 0;
}

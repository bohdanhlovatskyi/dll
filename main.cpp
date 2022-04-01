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

    int b = 2;
    std::vector<int> c;
    std::cout << a << std::endl;

    return 0;
}

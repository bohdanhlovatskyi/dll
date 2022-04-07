// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

#include <linked_list.hpp>

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;


    Node<int> n{5};

    LinkedList<int> a{};
    a.push_back(2);
    a.push_back(6);
    a.push_back(4);
    a.push_back(6);
    a.push_back(2);
    a.push_back(8);
    a.push_back(5);

    std::cout << a << std::endl;

    a.sort([](auto c, auto b){ return c < b; });

    std::cout << a << std::endl;

    return 0;
}

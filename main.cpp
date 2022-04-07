// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <map>
#include <vector>
#include <string>

#include <linked_list.hpp>

void usage_example();
void Test1();
void Test2();
void Test3();

template<>
std::ostream& operator<<(std::ostream& os, Node<std::pair<char, int>> node) {
    return os << "{" << node.data_.first << ", " << node.data_.second << "}";
}


std::map<char, int> mapping = {
        {'a', 12}, {'b', 2111}, {'c', 2121},
        {'d', 211}, {'e', 1}, {'f', 1121},
        {'g', 221}, {'h', 1111}, {'i', 11},
        {'j', 1222}, {'k', 212}, {'l', 1211},
        {'m', 22}, {'n', 21}, {'o', 111},
        {'p', 1221}, {'q', 2212}, {'r', 121},
        {'s', 111}, {'t', 2}, {'u', 112},
        {'v', 1112}, {'w', 122}, {'x', 2112},
        {'y', 2122}, {'z', 2211}
};

LinkedList<std::pair<char, int>> ll;

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;

    Test1();
    Test2();
    Test3();
}

void Test1() {
    // insert data and print it out
    for (auto const& [k, v] : mapping) {
        ll.push_back(std::pair{k, v});
    }

    std::cout << "-------- Test 1 --------" << std::endl;
    std::cout << ll << std::endl;
}

void Test2() {

    std::cout << "-------- Test 2 --------" << std::endl;
    ll.sort([](auto c, auto b){ return c.second < b.second; });
    std::cout << ll << std::endl;
}

void Test3() {
    // delete specific letters;
    std::cout << "-------- Test 3 --------" << std::endl;

    std::vector<char> to_delete = {'F', 'R', 'B', 'Z', 'A', 'M', 'G', 'R', 'C', 'Q', 'Y',  'C', 'N'};
    for (const auto& ltr : to_delete) {
        try {
            ll.remove_if([ltr](auto node){
                return std::tolower(node->data_.first) == std::tolower(ltr);
            });
        } catch (std::runtime_error err) {
            std::cerr << err.what() << std::endl;
            continue;
        }
    }

    std::cout << ll << std::endl;
}


void usage_example() {
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

    a.insert(10, 2);
    a.remove(3);

    std::cout << a << std::endl;
}

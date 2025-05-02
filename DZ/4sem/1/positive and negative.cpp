#include <iostream>
#include <stack>
#include<set>



int main()
{
    std::multiset<int> a = {1, -1, 74, -414152};
    std::multiset<int> pos = {};
    std::multiset<int> neg = {};
    for (const auto& elem : a) {
        if (elem > 0) {
            pos.insert(elem);
        }
        else {
            neg.insert(elem);
        }
    }
    std::cout << "Pos: " << std::endl;
    for (const auto& elem : pos) {
        std::cout << elem << std::endl;
    }

    std::cout << "Neg: ";
    for (const auto& elem : neg) {
        std::cout << elem << std::endl;
    }
}
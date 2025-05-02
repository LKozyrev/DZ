#include <iostream>
#include<vector>

template<typename Container>
void Print(const Container& container, const std::string& divider) {
    bool first = true;
    for (const auto& item : container) {
        if (!first) {
            std::cout << divider;
        }
        std::cout << item;
        first = false;
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> a{ 2, 7, 14, 8 };
    Print(a, "%");
}
#include <iostream>
#include <stack>

int main() {
    std::string a;
    std::cin >> a;
    bool reg = true;

    std::stack<int> Stack;
    for (std::string::iterator it = a.begin(); it != a.end(); it++) {
        if (*it == '{' || *it == '(' || *it == '[') {
            Stack.push(*it);
        }
        if (*it == '}') {
            if (Stack.empty() or Stack.top() != '{') {
                reg = false;
                break;
            }
            else {
                Stack.pop();
            }
        }
        if (*it == ')') {
            if (Stack.empty() or Stack.top() != '(') {
                reg = false;
                break;
            }
            else {
                Stack.pop();
            }
        }
        if (*it == ']') {
            if (Stack.empty() or Stack.top() != '[') {
                reg = false;
                break;
            }
            else {
                Stack.pop();
            }
        }
    }
    if (!Stack.empty()) {
        reg = false;
    }
    if (reg) {
        std::cout << "Regular";
    }
    else {
        std::cout << "Irregular";
    }
}
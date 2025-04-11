#include "Header.h"

std::vector<int> InputArray() {
	int size;
	std::cout << "Input size: ";
	std::cin >> size;
	std::vector<int> a;
	for (int i = 0; i < size; i++) {
		int b;
		std::cin >> b;
		a.push_back(b);
	}
	return a;
}
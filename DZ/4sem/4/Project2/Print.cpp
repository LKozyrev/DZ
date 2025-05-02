#include "Header.h"


void Print(std::vector<int> a) {
	for (auto it = a.begin(); it != a.end(); it++) {
		std::cout << *it << std::endl;
	}
}

#include "Header.h"
#include<algorithm>
void BubbleSort(std::vector<int>& a) {
	for (int i = 0; i < a.size(); i++) {
		bool swaps = false;
		for (int j = 0; j < a.size() - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				std::swap(a[j], a[j + 1]);
				swaps = true;
			}
		}
		if (!swaps) {
			break; // ћассив отсортирован, если не было перестановок
		}
	}
}
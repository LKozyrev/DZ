#include "Header.h"

void Mixed(std::vector<int>& a) {
	std::vector<int> a1(a.begin(), a.begin() + a.size()/2);
	std::vector<int> a2(a.begin() + a.size() / 2, a.end());

	QuickSort(a1);
	InsertionSort(a2);


	a.clear();
	a.insert(a.end(), a1.begin(), a1.end());
	a.insert(a.end(), a2.begin(), a2.end());

}
#include<iostream>
#define DYNAMIC_MEMORY(type, n) type *mas = new type(n)

int main() {
	int n = 5;
	DYNAMIC_MEMORY(int, n);
	for (int i = 0; i < n; i++) {
		mas[i] = i;
		std::cout << mas[i] << std::endl;
	}
}
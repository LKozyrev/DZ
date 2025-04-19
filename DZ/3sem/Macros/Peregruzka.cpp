#include<iostream>

using namespace std;
int Find(int *arr, int len, int elem) {
	int flag = false;
	for (int i = 0; i < len; i++) {
		if (arr[i]== elem){
			flag = true;
			return i;
			}
	}
	if (!flag) {
		cout << "Net takogo elementa";
		return -10000000;
	}
}

char Find(char* arr, int len, char elem) {
	int flag = false;
	for (int i = 0; i < len; i++) {
		if (arr[i] == elem) {
			flag = true;
			return i;
		}
	}
	if (!flag) {
		cout << "Net takogo elementa";
		return 's';
	}
}


float Find(float* arr, int len, float elem) {
	int flag = false;
	for (int i = 0; i < len; i++) {
		if (arr[i] == elem) {
			flag = true;
			return i;
		}
	}
	if (!flag) {
		cout << "Net takogo elementa";
		return -10000000.0;
	}
}
int main() {
	const int len = 10;
	int a[len];
	cout << "Input 10 element of the array: " << endl;
	for (int i = 0; i < len; i++) {
		cin >> a[i];
	}
	int elem;
	cout << endl << "Elem = ";
	cin >> elem;
	int*p = a;
	cout << endl << Find(p, len, elem);




	char aa[len];
	cout << "Input 10 element of the array: " << endl;
	for (int i = 0; i < 10; i++) {
		cin >> aa[i];
	}
	char elem;
	cout << endl << "Elem = ";
	cin >> elem;
	char* pp = aa;
	cout << endl << Find(pp, len, elem);




	float aaa[len];
	cout << "Input 10 element of the array: " << endl;
	for (int i = 0; i < 10; i++) {
		cin >> aaa[i];
	}
	float elem;
	cout << endl << "Elem = ";
	cin >> elem;
	float* ppp = aaa;
	cout << endl << Find(ppp, len, elem);
}
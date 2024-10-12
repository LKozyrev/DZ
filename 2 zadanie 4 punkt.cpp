#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = (i+1)*(i+1);
	}
	int Sum = 0;
	for (int i = 0; i < n; i++)
	{
		Sum += 1;
	}
	cout << Sum;
	delete arr;
}
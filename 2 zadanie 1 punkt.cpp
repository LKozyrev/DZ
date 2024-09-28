#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n;
	cin >> n;
	bool ProstoyeLiChislo = 1;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0 && i<n)
		{
			ProstoyeLiChislo = 0;
			cout << n / i;
			break;
		}
	}
	if (ProstoyeLiChislo && n!=1)
	{
		cout << "Prime";
	}
	if (n == 1)
	{
		cout << "Ni prostoye, ni sostavnoye";
	}
}
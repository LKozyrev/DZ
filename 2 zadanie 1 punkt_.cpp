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
		if (n % i == 0 && n > i)
		{
			cout << n / i;
			ProstoyeLiChislo = 0;
			break;
		}
	}
	if (ProstoyeLiChislo)
	{
		if (n == 1) {
			cout << "Ne prostoye i ne sostavnoye";
		}
		else
		{
			cout << "Prostoye";
		}
	}
}
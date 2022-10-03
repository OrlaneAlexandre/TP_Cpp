#include <iostream>
#include <math.h>
using namespace std;

bool isPrime(int nb)
{
	if (nb <= 1)
	{
		return false;
	}
	if (nb == 2)
	{
		return true;
	}
	for (int i = 2; i < ceil(sqrt(nb))+1; i++)
	{
		if (nb % i == 0)
		{
			return false;
		}
	}
	return true;
}


void main()
{
	int nb;
	cout << "Entrez des nombres : " << endl;
	while (cin >> nb)
	{
		if (isPrime(nb))
		{
			cout << nb << ": le nombre est premier \n";
		}
		else
		{
			cout << nb << ": le nombre n'est pas premier \n";
		}
	}
}

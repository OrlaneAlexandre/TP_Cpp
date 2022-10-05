#include <iostream>
#include <math.h>
#include <string>
#include <vector>
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
	while (cin >> nb)
	{
		if (isPrime(nb))
		{
			cout << nb << " is a prime: True \n";
		}
		else
		{
			cout << nb << " is a prime: False \n";
		}
	}
}
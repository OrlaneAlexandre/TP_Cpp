#include <iostream>
#include <math.h>
#include <string>
using namespace std;

bool isPrime(long long nb)
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


int main()
{
	long long nb;
	while (cin>>nb)
	{
		if (isPrime(nb))
		{
			cout << nb << " is a prime: True" << endl;
		}
		else
		{
			cout << nb << " is a prime: False" << endl;
		}
	}
	
	return 0;
}

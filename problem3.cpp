#include <random>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <vector>

/*
 * Greatest common denominator
 *
 * m 		argument 1
 * n 		argument 2
 *
 * returns
 * int 		greatest common denominator
 */
int gcd(int m, int n)
{
	int tmp;
	while (n != 0)
	{
		tmp = m;
		m = n;
		n = tmp%n;
	}
	return m;
}

/*
 * Modulous power per Fermats little theorem
 *
 * a 		base
 * x		exponenet
 * q		modulous
 *
 * returns
 * int 		a^x mod q
 */
unsigned long powmod(unsigned long long a, unsigned long long x, unsigned long long q)
{
    unsigned long long r = 1;
    x = x%q;
    while(x > 0)
    {
        if ((x&0x1) == 1)
        {
            r = (r*a)%q;
        }
        x = x>>1;
        a = (a*a)%q;
    }
    return r;
}

/*
 * Primality test using the Miller-Rabin algorithm
 *
 * n		number to test
 * k		accuracy of test
 *
 * returns
 * bool 	false if not prime
 *			true if most likely prime
 */
bool isPrimeMR(int n, int k)
{
	unsigned int x;
	unsigned int a;
	int d = n-1;
	int r = 0;
	if (n < 4)
	{
		return true;
	}
	// Write n-1 as 2^r*d
	while (((d>>1)<<1) == d)
	{
		d = d>>1;
		r++;
	}
	for (int i = 0; i < k; i++)
	{
		// Random number 1 < a < n-1
		a = rand()%(n-3) + 2;
		x = powmod(a, d, n);
		//std::cout << x << " " << a << " " << d << " " << n << std::endl;
		if (x == 1 || x == n-1)
		{
			goto cont; 
		}
		for (int j = 0; j < r-1; j++)
		{
			x = powmod(x, 2, n);
			if (x == n-1)
			{
				goto cont;
			}
		}
		return false;
		cont:;
	}
	return true;
}

/*
 * Helper g() function
 */
unsigned int g(unsigned int x, unsigned int n)
{
	return (x*x+1)%n;
}

/*
 * Factor a number using Pollard's Rho algorithm
 *
 * n 			number to factor
 *
 * returns
 * vector<int> 	prime factors
 */
void factorPR(int n, int s, std::vector<int>& v)
{
	unsigned int start = 2;
	if (n < 4)
	{
		v.push_back(n);
		std::cout << n << " is Prime" << std::endl;
		return;
	}
	while (start < n)
	{
		unsigned int x = start;
		unsigned int y = start;
		unsigned int d = 1;
		while (d == 1)
		{
			x = g(x, n);
			y = g(g(y, n), n);
			d = gcd(abs(x - y), n);
			//std::cout << x << " " << y << " " << d << std::endl;
		}
		if (d != n)
		{
			if (isPrimeMR((n/d), s) == true)
			{
				v.push_back(n/d);
				//std::cout << (n/d) << " is Prime" << std::endl;
			}
			else
			{
				//std::cout << "Non-prime " << (n/d) << std::endl;
				factorPR((n/d), s, v);
			}
			if (isPrimeMR(d, s) == true)
			{
				v.push_back(d);
				//std::cout << d << " is Prime d" << std::endl;
			}
			else
			{
				//std::cout << "Non-prime d " << d << std::endl;
				factorPR(d, s, v);
			}
			return;
		}
		else
		{
			start++;
		}
	}
	//std::cout << "Failure factoring non-prime: " << n << std::endl;
	v.push_back(n);
	return;
}



int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " number accuracy" << std::endl;
	}

	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	srand(std::time(0));

	if (isPrimeMR(n,k) == true)
	{
		std::cout << n << " is probably prime" << std::endl;
	}
	else
	{
		std::cout << n << " is not prime" << std::endl << "Factors:";
		std::vector<int> v = {};
		factorPR(n, k, v);
		std::sort(v.begin(), v.end());
		for (unsigned int i = 0; i < v.size(); i++)
		{
			std::cout << " " << v[i];
		}
		std::cout << std::endl;
	}
}
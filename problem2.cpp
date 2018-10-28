#include <iostream>
#include <stdio.h>
#include <utility>
#include <string>

int invert(int a, int n)
{
	int m = 1;
	int k = 1;
	while ((abs(k*n - m*a) != 1) || ((a*m)%n != 1))
	{
		if (a == 1) return 1;
		if (k*n > m*a) m++;
		else if (k*n < m*a) k++;
		else
		{
			std::cout << a << " is not invertable mod " << n << std::endl << "m = " << m << ", k = " << k << std::endl;
			return 0;
		}
	}
	return m;
}

std::pair<int,int> add(std::pair<int,int> p1, std::pair<int,int> p2, std::pair<int,int> curve, int mod)
{
	int m;
	int n;
	if ((p1.first == 0 && p1.second == 0)) return p2;
	if ((p2.first == 0 && p2.second == 0)) return p1;
	if (p1.first == p2.first)
	{
		if (p1.second == p2.second)
		{
			m = 3*p1.first*p1.first+curve.first;
			n = invert(2*p1.second, mod);
			m = (m*n)%mod;
		}
		else
		{
			return std::make_pair(0,0);
		}
	}
	else
	{
		m = (p2.second - p1.second);
		n = p2.first - p1.first;
		while (n < 0) n+= mod;
		n = invert (n, mod);
		m = (m*n)%mod;
	}
	int x = (m*m) - p1.first - p2.first;
	int y = (m*(p1.first - x)) - p1.second;
	while (x < 0) x+= mod;
	while (y < 0) y+= mod;
	return std::make_pair(x%mod, y%mod);
}

std::pair<int,int> mul(std::pair<int,int> p, int sca, std::pair<int,int> curve, int mod)
{
	std::pair<int,int> ans = p;
	for (int i = 1; i < sca; i++)
	{
		ans = add(p, ans, curve, mod);
		//std::cout << "(" << p.first << "," << p.second << ") * " << (i+1) << " = (" << ans.first << "," << ans.second << ")" << std::endl;
	}
	return ans;
}

int main(int argc, char* argv[])
{
	if (argc < 1)
	{
		//std::cerr << "Usage " << argv[0] << std::endl
	}
	int m = 11;
	std::pair<int,int> c = std::make_pair(1,7);
	std::pair<int,int> g = std::make_pair(3,2);
	/*
	//std::pair<int,int> q = std::make_pair(9,7);
	std::pair<int,int> ans = g;
	for (int i = 2; i < 14; i++)
	{
		ans = add(g, ans, c, 11);
		std::cout << i << "G = (" << ans.first << "," << ans.second << ")" << std::endl;
	}
	*/
	std::string command;
	std::string in1;
	std::string in2;
	std::pair<int,int> p1;
	std::pair<int,int> p2;
	std::pair<int,int> res;
	int sca;
	int cma;
	while(1)
	{
		std::cout << "> ";
		std::cin >> command;
		if (command == "add")
		{
			std::cin >> in1 >> in2;	
			for (int i = 0; i < in1.size(); i++)
			{
				if(in1[i] == ',')
				{
					cma = i;
					p1 = std::make_pair(atoi(in1.substr(0, cma).c_str()),atoi(in1.substr(cma+1).c_str()));
					//std::cout << in1.substr(0,cma) << " " << in1.substr(cma+1) << std::endl;
					break;
				}
			}
			for (int i = 0; i < in2.size(); i++)
			{
				if(in2[i] == ',')
				{
					cma = i;
					p2 = std::make_pair(atoi(in2.substr(0, cma).c_str()),atoi(in2.substr(cma+1).c_str()));
					//std::cout << "|"  << in2 << "|" << std::endl;
					break;
				}
			}

			res = add(p1, p2, c, m);
			std::cout << "(" << p1.first << "," << p1.second << ") + (" << p2.first << "," << p2.second << ") = (" << res.first << "," << res.second << ")" << std::endl;
		}
		else if (command == "mul")
		{
			std::cin >> in1 >> in2;	
			for (int i = 0; i < in1.size(); i++)
			{
				if(in1[i] == ',')
				{
					cma = i;
					p1 = std::make_pair(atoi(in1.substr(0, cma).c_str()),atoi(in1.substr(cma+1).c_str()));
					//std::cout << in1.substr(0,cma) << " " << in1.substr(cma+1) << std::endl;
					break;
				}
			}
			sca = atoi(in2.c_str());
			res = mul(p1, sca, c, m);
			std::cout << "(" << p1.first << "," << p1.second << ") * "<< sca << " = (" << res.first << "," << res.second << ")" << std::endl;
		}
		else if (command == "invert")
		{
			std::cin >> in1 >> in2;
			std::cout << in1 << "^-1 mod " << in2 << " = " << invert(atoi(in1.c_str()), atoi(in2.c_str())) << std::endl;
		}
		else if (command == "exit")
		{
			break;
		}
		else
		{
			std::cout << "Invalid command: \"" << command << '"' <<std::endl;
		}
	}
}
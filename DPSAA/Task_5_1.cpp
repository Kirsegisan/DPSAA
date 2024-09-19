#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <Windows.h>
#include <array>
#include <bitset>
#include <vector>


void Task_5_1() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned char x = 255;
	unsigned char maska = 1;
	x = x & (~(maska << 4));
	const char n = sizeof(int)*2;
	std::cout << bitset<n>(x) << std::endl;
}


void T1V()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	unsigned char x = 25;
	const int n = sizeof(int) * 8;
	unsigned char maska = (1 << n - 1);
	for (int i = 1; i <= n; i++)
	{
		std::cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
	}
	std::cout << std::endl;
}


vector<int> T2A(int inputData[], int size) 
{
	const char n = sizeof(int) * 2;
	unsigned char x = 0;
	unsigned char maska = 0;
	for (int i = 0; i < size; i++)
	{
		maska = 1 << inputData[i] - 1;
		std::cout << bitset<n>(maska) << std::endl;
		x = (x | maska);
	}
	std::cout << bitset<n>(x);
	vector<int> outData;
	for (int i = 0; i < 8; i++)
	{
		maska = 1 << i;
		if (x == (x | maska))
		{
			outData.push_back(i + 1);
		}
	}
	std::cout << std::endl;
	return (outData);
}

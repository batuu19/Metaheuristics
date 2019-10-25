// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

int main()
{
	//constexpr size_t size = std::numeric_limits<size_t>().max();
	constexpr size_t size = 2 << 15;

	int arr[size];
	int* ptr = new int[size];
	std::vector<int> vec(size,1);

	size_t i = 0;

	for (size_t j = 0; j < (2<<11); j++)
	{
		while (i < size)
		{
			arr[i] = i;
			ptr[i] = i;
			//vec[i] = i;
			i++;
		}
	}
	for (unsigned long long int j = 0; j < ULLONG_MAX; j++)
	{
		i = 0;
		int x;

		while (i < size)
		{
			x = arr[i];
			x = vec[i];
			x = ptr[i];
			i++;
		}
	}
	delete arr;
	delete[]ptr;

	std::cout << "Hello World!\n" << size;
}
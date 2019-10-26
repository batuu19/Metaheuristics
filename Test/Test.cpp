// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

int main()
{
	size_t size = 20;
	int* arr = new int[size];
	std::vector<int> vec(size, 1);

	for (size_t i = 0; i < size; i++)
	{
		arr[i] = i;
	}


	std::cout << "Hello World!\n";
	delete[]arr;
}
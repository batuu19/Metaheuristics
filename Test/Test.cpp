// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <set>
#include <numeric>
#include <algorithm>

int main()
{
	size_t size = 20;
	std::vector<int> vec(size);
	std::iota(vec.begin(), vec.end(), 0);
	std::vector<int> vec2(size, -1);
	for (int i = 10; i < 15; i++)
	{
		vec2[i] = vec[i];
	}
	
}
// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <set>
#include <numeric>
#include <algorithm>
#include <random>
#include <fstream>

int main()
{
	std::normal_distribution<> dist(0,5);
	std::mt19937 rng(std::random_device{}());
	std::ofstream file;
	auto x = dist.max();
	file.open("test.csv");
	file << "value"<<std::endl;
	size_t count = 1000;
	for (size_t i = 0; i < count; i++)
	{
		file << dist(rng) << std::endl;
	}
}
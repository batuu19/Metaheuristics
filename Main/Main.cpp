
#include <random>
#include <iostream>
#include <cstdio>

#include "Loader.h"
#include "Problem.h"
#include "Loader.h"
#include "Utils.h"

#include "AlgorithmsRunner.h"

int main()
{
	std::mt19937 rng(std::random_device{}());
	std::string instanceName = "kroA150";
	Problem problem = Loader::loadData(TSP_DIRECTORY + instanceName + ".tsp");
	AlgorithmsRunner runner = AlgorithmsRunner(4);
	runner.run(rng, "");

	//AlgorithmsRunner::configTester(rng);

	/*
	size_t first, second;


	while (swapCount > 1)
	{
		first = dist(rng);
		second = dist(rng);
		if (
			citiesCount - second < 2 * swapCount ||
			(int)second - (int)first < 2 * (int)swapCount
			)
		{
			for (size_t i = 0; i < swapCount; i++)
				mutateSwap(rng, false);
		}
		else
		{
			std::swap_ranges(cities + first, cities + first + swapCount, cities + second);
		}

		swapCount /= 2;
	}
	if(cf)
		calculateFitness();*/
}

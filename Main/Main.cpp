
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
	AlgorithmsRunner runner = AlgorithmsRunner(3);
	runner.run(rng);
}

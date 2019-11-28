
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
	AlgorithmsRunner runner;
	runner.runAlgorithm(rng, AlgorithmType::GA_TS, Config::getGATSConfig(100, 100, 0.5f, 0.02f,10,10, 8), "kroA100");
}

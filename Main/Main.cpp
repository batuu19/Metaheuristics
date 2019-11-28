
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
	runner.runAlgorithm(rng, AlgorithmType::GENETIC, Config::getGAConfig(200, 1000, 0.80f,0.02f, 30), "kroA150");
}

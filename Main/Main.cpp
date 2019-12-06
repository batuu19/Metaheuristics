
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
	AlgorithmsRunner runner = AlgorithmsRunner(4);
	runner.run(rng, "");

	//std::string instanceName = "kroA150";
	//Problem problem = Loader::loadData(TSP_DIRECTORY + instanceName + ".tsp");
	//runner.runAlgorithm(rng, AlgorithmType::TABU,
	//	Config::getTabuConfig(0, "testTabu", 14, 1500),problem);

	//AlgorithmsRunner::configTester(rng);

}


#include <random>
#include <iostream>
#include <cstdio>

#include "Loader.h"
#include "GAAlgorithm.h"
#include "Problem.h"
#include "Loader.h"
#include "Utils.h"

#include "TabuAlgorithm.h"
#include "WAlgorithm.h"

int main()
{
    //std::string filename = "berlin11_modified.tsp";
    std::string filename = "berlin52.tsp";
    //std::string filename = "kroA100.tsp";
    std::string configFilename = "config.cfg";

	auto problem = Loader::loadData(TSP_DIRECTORY + filename);
//	auto configs = Loader::loadConfigs(configFilename);



	std::mt19937 rng(std::random_device{}());

	WAlgorithm alg = WAlgorithm(problem);
	//TabuAlgorithm alg = TabuAlgorithm(problem);
	alg.run(rng);
	system("pause");
}

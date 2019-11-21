
#include <random>
#include <iostream>
#include <cstdio>

#include "Loader.h"
#include "Problem.h"
#include "Loader.h"
#include "Utils.h"

#include "GAAlgorithm.h"
#include "TabuAlgorithm.h"
#include "SAAlgorithm.h"

int main()
{
    //std::string filename = "berlin11_modified.tsp";
    std::string filename = "kroA100.tsp";
    //std::string filename = "kroA100.tsp";
    std::string configFilename = "config.cfg";

	auto problem = Loader::loadData(TSP_DIRECTORY + filename);
//	auto configs = Loader::loadConfigs(configFilename);



	std::mt19937 rng(std::random_device{}());

	MetaAlgorithm* algorithm = 
		new GAAlgorithm(problem, Config::getGAConfig(
			500, 500, 0.85f, 0.1f, 100,
			Mutation::SWAP,Crossover::PMX));
	algorithm->run(rng);

	delete algorithm;

	//system("pause");
}

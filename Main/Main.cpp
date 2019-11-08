
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
			1000, 100, 0.9f, 0.05f, 10,
			Mutation::SWAP,Crossover::OX));
	//MetaAlgorithm* algorithm =
	//	new SAAlgorithm(problem, Config::getSAConfig(1500, 0.995, 3, 1000));
	algorithm->run(rng);

	//SAAlgorithm alg = SAAlgorithm(problem);
	//TabuAlgorithm alg = TabuAlgorithm(problem);
	//alg.run(rng);
	delete algorithm;
	//system("pause");
}

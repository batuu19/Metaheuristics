
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
			200, 200, 0.85f, 0.1f, 100,
			Mutation::SWAP,Crossover::PMX));
	algorithm->run(rng);

	delete algorithm;

	/*std::vector<int> v1 = { 8,4,7,3,6,2,5,1,9,0 };
	std::vector<int> v2 = { 0,1,2,3,4,5,6,7,8,9 };
	Creature p1 = Creature(nullptr, v1);
	Creature p2 = Creature(nullptr, v2);
	auto c1 = p1.crossoverPMX(p2, rng);*/

	//system("pause");
}

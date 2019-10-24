
//#include "Main.h"
#include <random>
#include <iostream>
#include "Loader.h"
#include "Algorithm.h"
#include "Problem.h"
#include "Loader.h"
#include "Utils.h"

int main()
{
	//std::cout << "Hello World!\n";
	//std::string command = "ls " + std::string(TSP_DIRECTORY);
	//std::string filename = "berlin11_modified.tsp";

	std::string filename = "berlin11_modified.tsp";
	std::string configFilename = "config.cfg";

	auto problem = Loader::loadData(TSP_DIRECTORY + filename);
	auto configs = Loader::loadConfigs(configFilename);

	std::mt19937 rng(std::random_device{}());

	Algorithm algorithm(configs[0], problem.getDistanceMatrix());
	algorithm.run(rng);



	system("pause");
}

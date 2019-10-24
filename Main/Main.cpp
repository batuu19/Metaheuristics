
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
	//std::string filename = "berlin11_modified.tsp";
	std::string filename = "berlin52.tsp";
	std::string configFilename = "config.cfg";

	auto problem = Loader::loadData(TSP_DIRECTORY + filename);
	auto configs = Loader::loadConfigs(configFilename);

	//std::vector<size_t> popSizes = { 10,50,100,200,500,1000 };
	//std::vector<size_t> generationCounts = { 10,50,100,200,500,1000 };
	//std::vector<float> pxs = {0.5f,0.7f,0.9f,0.99f,1.f};
	//std::vector<float> pms = {0.005f,0.01,0.03f,0.1f,0.3f,0.5f};
	//std::vector<size_t> tSizes = {10,15,25,50,200};

	std::vector<size_t> popSizes = { 100,500,1000 };
	std::vector<size_t> generationCounts = { 100,200,500,1000 };
	std::vector<float> pxs = { 0.9f,0.99f,1.f };
	std::vector<float> pms = { 0.03f,0.1f,0.3f };
	std::vector<size_t> tSizes = { 10,50,200 };

	size_t nextID = configs.size() + 1;

	bool extra = false;

	if (extra)
		for (auto pS : popSizes)
			for (auto gC : generationCounts)
				for (auto px : pxs)
					for (auto pm : pms)
						for (auto tSize : tSizes)
							configs.push_back(Config(nextID, pS, gC, px, pm, tSize));


	std::mt19937 rng(std::random_device{}());

	for (auto& config : configs)
	{
		Algorithm algorithm(config, problem.getDistanceMatrix());
		algorithm.run(rng);
		config.saveToFile();

	}





	//system("pause");
}

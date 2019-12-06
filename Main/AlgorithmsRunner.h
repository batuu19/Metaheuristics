#pragma once
#include "MetaAlgorithm.h"
#include "GAAlgorithm.h"
#include "GreedyAlgorithm.h"
#include "SAAlgorithm.h"
#include "TabuAlgorithm.h"
#include "GATSAlgorithm.h"
#include "GAAgeAlgorithm.h"
#include "Loader.h"
#include <random>
#include <memory>
#include <algorithm>
class Instance
{
public:
	size_t id;
	std::string name;
	size_t optimumValue;
	static std::vector<Instance> getInstances()
	{
		return {
			{0,"kroA100",	 21282,},
			{1,"kroA150",	 26524,},
			//{2,"kroA200",	 29368,},
			/*{3,"fl417",		 11861,},
			{4,"ali535",	 202339,},
			{5,"gr666",		 294358,},
			{6,"nrw1379",	 56638,},
			{7,"pr2392",	 378032,},*/
		};
	}
	static const size_t count = 2;
private:
	Instance(size_t id, std::string name, size_t optimumValue)
		:
		id(id),
		name(name),
		optimumValue(optimumValue)
	{};
};
enum class AlgorithmType
{
	RANDOM,
	GREEDY,
	GENETIC,
	TABU,
	SA,
	NONE,//end of main algs
	GA_TS,
	GA_AGED,
};

static constexpr size_t ALGORITGM_COUNT = static_cast<size_t>(AlgorithmType::NONE);
const static std::vector<Instance> instances = Instance::getInstances();

class AlgorithmsRunner
{
public:
	AlgorithmsRunner(size_t runCount = 1);
	AlgorithmsRunner(const AlgorithmsRunner&) = delete;
	AlgorithmsRunner& operator=(const AlgorithmsRunner&) = delete;
	~AlgorithmsRunner();
	float*** run(std::mt19937& rng);
	void run(std::mt19937& rng, std::string filename);
	static float runAlgorithm(std::mt19937& rng,AlgorithmType algType,Config config,std::string instanceName);
	static float runAlgorithm(std::mt19937& rng,AlgorithmType algType,Config config,const Problem& problem);
	static std::string getCSVLine(float* results, size_t runCount);
	static void saveResultsToFiles(float*** results, size_t runCount, std::string prefix = "",std::string path = "CSV\\results\\");
	static int configTester(std::mt19937& rng, AlgorithmType algType,
		const std::vector<Config>& configs,int repeats, const Problem& problem);
	static void configTester(std::mt19937& rng);
private:
	size_t runCount;
	float*** cache;
};

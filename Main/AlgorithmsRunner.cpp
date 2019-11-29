#include "AlgorithmsRunner.h"

AlgorithmsRunner::AlgorithmsRunner(size_t runCount)
	:
	runCount(runCount)
{
	cache = new float** [Instance::count];// [instance] [algType] [num]
	for (size_t inst = 0; inst < Instance::count; inst++)
	{
		cache[inst] = new float* [static_cast<int>(AlgorithmType::NONE)];
		for (size_t alg = 0; alg < static_cast<int>(AlgorithmType::NONE); alg++)
		{
			cache[inst][alg] = new float[runCount];
		}
	}
}

AlgorithmsRunner::~AlgorithmsRunner()//good?
{
	for (size_t inst = 0; inst < Instance::count; inst++)
	{
		for (size_t alg = 0; alg < static_cast<int>(AlgorithmType::NONE); alg++)
		{
			delete[] cache[inst][alg];
		}
		delete[] cache[inst];
	}

	delete[] cache;
}

float*** AlgorithmsRunner::run(std::mt19937& rng)
{
	MetaAlgorithm* algorithm;
	float*** results = cache;
	for (auto instance : instances)
	{
		std::cout << instance.name << " ";
		Problem problem = Loader::loadData(TSP_DIRECTORY + instance.name + ".tsp");
		size_t totalCreatureCount = 100;
		for (size_t i = 0; i < runCount; i++)
		{
			std::cout << i << " ";
			Config greedyConfig = Config::getGreedyConfig(i, instance.name);
			Config gaConfig = Config::getGAConfig(i, instance.name, 1000, 1500, 0.85f, 0.005f, 50, Mutation::SWAP, Crossover::OX);
			Config tsConfig = Config::getTabuConfig(i, instance.name, 4, totalCreatureCount);
			Config saConfig = Config::getSAConfig(i, instance.name, 1500.f, 0.995, 5, totalCreatureCount);

			results[instance.id][0][i] = Creature::getRandomCreature(problem, rng).getFitness();

			algorithm = new GreedyAlgorithm(problem, greedyConfig);
			results[instance.id][1][i] = algorithm->run(rng);
			delete algorithm;

			algorithm = new GAAlgorithm(problem, gaConfig);
			results[instance.id][2][i] = algorithm->run(rng);
			delete algorithm;

			algorithm = new TabuAlgorithm(problem, tsConfig);
			results[instance.id][3][i] = algorithm->run(rng);
			delete algorithm;

			algorithm = new SAAlgorithm(problem, saConfig);
			results[instance.id][4][i] = algorithm->run(rng);
			delete algorithm;
		}
		std::cout << std::endl;

	}
	saveResultsToFiles(results, runCount);
	return results;
}

void AlgorithmsRunner::run(std::mt19937& rng, std::string filename)
{
	auto results = run(rng);
	saveResultsToFiles(results, runCount);
}

float AlgorithmsRunner::runAlgorithm(std::mt19937& rng, AlgorithmType algType,Config config, std::string instanceName)
{
	MetaAlgorithm* algorithm;
	Problem problem = Loader::loadData(TSP_DIRECTORY + instanceName + ".tsp");
	float best;
	switch (algType)
	{
	case AlgorithmType::RANDOM:
		return Creature::getRandomCreature(problem, rng).getFitness();
	case AlgorithmType::GREEDY:
		algorithm = new GreedyAlgorithm(problem, config);
		break;
	case AlgorithmType::GENETIC:
		algorithm = new GAAlgorithm(problem, config);
		break;
	case AlgorithmType::TABU:
		algorithm = new TabuAlgorithm(problem, config);
		break;
	case AlgorithmType::SA:
		algorithm = new SAAlgorithm(problem, config);
		break;
	case AlgorithmType::GA_TS:
		algorithm = new GATSAlgorithm(problem, config);
		break;
	case AlgorithmType::GA_AGED:
		algorithm = new GAAgeAlgorithm(problem, config);
		break;
	default:
		return -1.f;
	}

	best = algorithm->run(rng);
	delete algorithm;
	return best;
}

std::string AlgorithmsRunner::getCSVLine(float* results, size_t runCount)
{
	std::stringstream ss;
	for (size_t i = 0; i < runCount; i++)
	{
		ss << results[i] << ",";
	}
	return ss.str();
}

void AlgorithmsRunner::saveResultsToFiles(float*** results, size_t runCount, std::string prefix, std::string path)
{
	std::string filename = "result.csv";
	std::shared_ptr<std::ofstream> randFile, greedyFile, gaFile, tabuFile, saFile;
	randFile = std::make_shared<std::ofstream>();
	greedyFile = std::make_shared<std::ofstream>();
	gaFile = std::make_shared<std::ofstream>();
	tabuFile = std::make_shared<std::ofstream>();
	saFile = std::make_shared<std::ofstream>();
	std::vector<std::shared_ptr<std::ofstream>> files{ randFile, greedyFile, gaFile, tabuFile, saFile };
	randFile->open(path + prefix + "rn_" + filename);
	greedyFile->open(path + prefix + "gr_" + filename);
	gaFile->open(path + prefix + "ga_" + filename);
	tabuFile->open(path + +"ts_" + filename);
	saFile->open(path + prefix + "sa_" + filename);



	for (auto& file : files)
	{
		*file << "name,optimum,";
		for (size_t i = 0; i < runCount; i++)
			*file << "best" << i<<",";
		*file << std::endl;
	}

	for (size_t f = 0; f < files.size(); f++)
	{
		for (size_t inst = 0; inst < Instance::count; inst++)
		{
			*files[f] << instances[inst].name << "," << instances[inst].optimumValue;
			*files[f] << "," << getCSVLine(results[inst][f], runCount);
			*files[f] << std::endl;
		}
	}
}

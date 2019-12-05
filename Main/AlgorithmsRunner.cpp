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
			Config gaConfig = Config::getGAConfig(i, instance.name, 1200, 1200, 0.8f, 0.01f,150);
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
	return runAlgorithm(rng, algType, config, Loader::loadData(TSP_DIRECTORY + instanceName + ".tsp"));	
}

float AlgorithmsRunner::runAlgorithm(std::mt19937& rng, AlgorithmType algType, Config config, const Problem& problem)
{
	MetaAlgorithm* algorithm;
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

int AlgorithmsRunner::configTester(std::mt19937& rng, AlgorithmType algType, 
	const std::vector<Config>& configs,int repeats, const Problem& problem)
{
	int bestConfigId = 0;
	float best = std::numeric_limits<float>::max();
	float algBest;
	for (size_t i = 0; i < configs.size(); i++)
	{
		std::cout << "Config " << i << "/" << configs.size() << std::endl;
		int sum = 0;
		for (int i = 0; i < repeats; i++)
		{
			sum += runAlgorithm(rng, algType, configs[i], problem);
		}
		algBest = sum / repeats;
		if (algBest < best)
		{
			best = algBest;
			bestConfigId = i;
		}

	}
	return bestConfigId;
}

void AlgorithmsRunner::configTester(std::mt19937& rng)
{
	int repeats = 5;
	std::vector<int> popSizes = { 1200 };
	std::vector<int> generationCounts = { 1200 };
	std::vector<float> pxs = { 0.5f,0.8f,0.95f };
	std::vector<float> pms = {0.02f,0.01f,0.008f};
	std::vector<int> tSizes = { 5,25,70};
	std::vector<Config> configs;
	size_t configNum = 0;
	configs.reserve(popSizes.size() * generationCounts.size() *
		pxs.size() * pms.size() * tSizes.size());
	for (auto popSize : popSizes)
	for (auto generationCount : generationCounts)
	for (auto px : pxs)
	for (auto pm : pms)
	for (auto tSize : tSizes)
	{
		configs.push_back(Config::getGAConfig(configNum, popSize, generationCount, px, pm, tSize));
		configNum++;
	}

	std::string instanceName = "kroA200";
	Problem problem = Loader::loadData(TSP_DIRECTORY + instanceName + ".tsp");
	int bestConfigId = configTester(rng, AlgorithmType::GENETIC, configs, repeats, problem);
	Config config = configs[bestConfigId];

	std::ofstream bestConfigFile;
	bestConfigFile.open("best.txt");
	bestConfigFile << "id " << bestConfigId << std::endl;
	bestConfigFile << "popSize" << config.popSize << std::endl;
	bestConfigFile << "generations" << config.generations << std::endl;
	bestConfigFile << "px" << config.px << std::endl;
	bestConfigFile << "pm" << config.pm << std::endl;
	bestConfigFile << "tSize" << config.tSize << std::endl;
	bestConfigFile.close();
}

#include "Loader.h"

Problem Loader::loadData(const std::string& filename)
{
	std::string name;
	std::string type;
	std::string comment;
	int dimension;
	std::string edgeWeightType;
	std::vector<Point> nodes;

	std::ifstream file;
	file.open(TSP_DIRECTORY + filename);

	std::string line;
	std::vector<std::string> lines;
	while (getline(file, line) && line != LINE_EOF)
		lines.push_back(line);

	bool nowNodes = false;
	for (const auto& l : lines)
	{
		std::stringstream ss = std::stringstream(l);
		std::string word;

		if (!nowNodes)
		{
			ss >> word;
			//TODO optimize
			if (word == "NAME:")
			{
				ss >> name;
			}
			else if (word == "TYPE:")
			{
				ss >> type;
			}
			//TODO COMMENT?
			else if (word == "DIMENSION:")
			{
				ss >> word;
				dimension = std::stoi(word);
			}
			else if (word == "EDGE_WEIGHT_TYPE:")
			{
				ss >> edgeWeightType;
			}
			else if (word == "NODE_COORD_SECTION")
			{
				nowNodes = true;
			}
		}
		else//now nodes
		{
			nodes.push_back(getPointFromLine(l));
		}
	}

	return Problem(name, type, comment, edgeWeightType, nodes);
}

std::vector<Config> Loader::loadConfigs(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	std::string line;
	getline(file, line);
	size_t count = getConfigVar<int>(line);
	size_t popSize;
	size_t generations;
	float px, pm;//crossover, mutation
	size_t tSize;//turniej size
	std::vector<Config> configs;
	for (size_t i = 0; i < count; i++)
	{
		getline(file, line);//empty line between
		getline(file, line);//config num
		getline(file, line);//popsize
		popSize = getConfigVar<int>(line);
		getline(file, line);//generations
		generations = getConfigVar<int>(line);
		getline(file, line);//PX
		px = getConfigVar<float>(line);
		getline(file, line);//PM
		pm = getConfigVar<float>(line);
		getline(file, line);//tSize
		tSize = getConfigVar<int>(line);
		configs.push_back({ popSize,generations,px,pm,tSize });
	}
	return configs;
}

std::vector<Point> Loader::debugLoadNodes(const std::string& filename)
{
	std::ifstream file;
	file.open(TSP_DIRECTORY + filename);
	std::string line;
	do
	{
		getline(file, line);
	} while (line != LINE_NODES_BEGIN);
	std::vector<Point> result;
	getline(file, line);
	do
	{
		result.push_back(getPointFromLine(line));
		getline(file, line);
	} while (line != LINE_EOF);

	return result;
}

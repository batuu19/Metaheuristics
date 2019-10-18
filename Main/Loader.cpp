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
	while (getline(file, line) && line != "EOF")
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
			float x, y;
			ss >> word;//count
			ss >> word;
			x = std::stof(word);
			ss >> word;
			y = std::stof(word);

			nodes.push_back({ x,y });
		}
		

	}

	return Problem(name,type,comment,edgeWeightType,nodes);
}

std::vector<Config> Loader::loadConfigs(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	std::string line;
	std::vector<std::string> lines;
	getline(file, line);
	std::stringstream ss = std::stringstream(line);
	std::string word;
	ss >> word;//placeholder
	ss >> word;
	size_t count = stoi(word);
	size_t popSize;
	size_t generations;
	float px, pm;//crossover, mutation
	for (size_t i = 0; i < count; i++)
	{
		getline(file, line);//empty line between
		getline(file, line);//config num
		getline(file, line);//popsize
		popSize = getConfigInt(line);
		getline(file, line);//generations
		generations = getConfigInt(line);
		getline(file, line);//PX
		px = getConfigFloat(line);
		getline(file, line);//PM
		pm = getConfigFloat(line);
	}
	//todo
	return std::vector<Config>();
}

int Loader::getConfigInt(std::string line)
{
	std::stringstream ss = std::stringstream(line);
	std::string word;
	ss >> word;
	ss >> word;
	return stoi(word);
}

float Loader::getConfigFloat(std::string line)
{
	std::stringstream ss = std::stringstream(line);
	std::string word;
	ss >> word;
	ss >> word;
	return stof(word);
}

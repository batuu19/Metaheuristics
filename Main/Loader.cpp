#include "Loader.h"

Algorithm Loader::load(const std::string& filename)
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

	return Algorithm(name,type,comment,edgeWeightType,nodes);
}

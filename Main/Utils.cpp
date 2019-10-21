#include "Utils.h"

std::vector<std::string> splitString(std::string s)
{
	std::stringstream ss(s);
	std::vector<std::string> result;
	std::string word;
	while (!ss.eof())
	{
		ss >> word;
		result.push_back(word);
	}

	return result;
}

Point getPointFromLine(std::string line)
{
	auto split = splitString(line);
	return { std::stof(split[1]),std::stof(split[2]) };
}

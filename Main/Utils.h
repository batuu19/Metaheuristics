#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <random>
#include "Math.h"

std::vector<std::string> splitString(std::string s);

Point getPointFromLine(std::string line);//error here(takes EOF)

template<typename T>
T getConfigVar(std::string line);

template<>
inline int getConfigVar(std::string line)
{
	auto split = splitString(line);
	return std::stoi(split[1]);
}

template<>
inline float getConfigVar(std::string line)
{
	auto split = splitString(line);
	return std::stof(split[1]);
}

template<>
inline std::string getConfigVar(std::string line)
{
	auto split = splitString(line);
	return split[1];
}
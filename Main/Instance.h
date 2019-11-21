#pragma once
#include <string>
#include <vector>
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
			{2,"kroA200",	 29368,},
			{3,"fl417",		 11861,},
			{4,"ali535",	 202339,},
			//{5,"gr666",		 294358,},
			//{6,"nrw1379",	 56638,},
			//{7,"pr2392",	 378032,},
		};
	}
	static const size_t count = 8;
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
	NONE,
};
static constexpr size_t ALGORITGM_COUNT = 5;
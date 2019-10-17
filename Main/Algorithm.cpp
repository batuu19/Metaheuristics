#include "Algorithm.h"


Algorithm::Algorithm()
	:Algorithm("unknown","","no comment","",std::vector<Point>())
{
}

Algorithm::Algorithm(
	std::string name, std::string type, std::string comment, std::string edgeWeightType, 
	const std::vector<Point>& nodes) :
	name(name),
	type(type),
	comment(comment),
	edgeWeightType(edgeWeightType),
	nodes(nodes)
{
}

#include "Problem.h"


Problem::Problem()
	:Problem("unknown","","no comment","",std::vector<Point>())
{
}

Problem::Problem(
	std::string name, std::string type, std::string comment, std::string edgeWeightType, 
	const std::vector<Point>& nodes) :
	name(name),
	type(type),
	comment(comment),
	edgeWeightType(edgeWeightType),
	nodes(nodes)
{
}

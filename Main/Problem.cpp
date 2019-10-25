#include "Problem.h"


Problem::Problem(
	std::string name, std::string type, std::string comment, std::string edgeWeightType,
	const std::vector<Point>& nodes) :
	name(name),
	type(type),
	comment(comment),
	dimension(nodes.size()),
	edgeWeightType(edgeWeightType),
	nodes(nodes)
{
	distanceMatrix = new DistanceMatrix(nodes);
}

Problem::Problem(const std::vector<Point>& nodes)
	:
	nodes(nodes),
	dimension(nodes.size())
{
	distanceMatrix = new DistanceMatrix(nodes);
}

Problem::Problem(const Problem& other)
	:
	dimension(other.dimension),
	distanceMatrix(other.distanceMatrix)
{}

Problem& Problem::operator=(const Problem& other)
{
	this->name = other.name;
	this->type = other.type;
	this->comment = other.comment;
	this->dimension = other.dimension;
	this->edgeWeightType = other.edgeWeightType;
	this->nodes = other.nodes;
	this->distanceMatrix = other.distanceMatrix;
	return *this;
}

Problem::~Problem()
{
	delete distanceMatrix;
}

size_t Problem::getDimension() const
{
	return dimension;
}

DistanceMatrix* Problem::getDistanceMatrix() const
{
	return distanceMatrix;
}


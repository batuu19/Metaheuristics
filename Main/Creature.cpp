#include "Creature.h"

Creature::Creature(DistanceMatrix* distanceMatrix, const std::vector<int>& cities)//private
	:
	citiesCount(cities.size()),
	cities(cities),
	dist(0, citiesCount-1),
	distanceMatrix(distanceMatrix)
{
	calculateFitness();//needed,optimize?
}

Creature::Creature(DistanceMatrix* distanceMatrix)
	:
	citiesCount(distanceMatrix->getSize()),
	cities(citiesCount),
	distanceMatrix(distanceMatrix)
{}//no cities yet, do not calculate fitness

Creature::Creature(const Creature& other)
	:
	citiesCount(other.citiesCount),
	cities(other.cities),
	dist(0, citiesCount-1),
	distanceMatrix(other.distanceMatrix),
	fitness(other.fitness)
{}

Creature& Creature::operator=(const Creature& other)
{
	this->citiesCount = other.citiesCount;
	this->cities = other.cities;//?
	this->dist = std::uniform_int_distribution<size_t>(0, citiesCount-1);//???
	this->distanceMatrix = other.distanceMatrix;
	this->fitness = other.fitness;
	return *this;
}

Creature::~Creature()
{}//do nothing, do not delete distance matrix

void Creature::init(std::mt19937& rng)
{
	std::iota(cities.begin(), cities.end(), 0);//0,1,2,3,...
	std::shuffle(cities.begin(), cities.end(), rng);
	calculateFitness();
}

void Creature::mutateSwap(std::mt19937& rng)
{
	size_t first, second;
	getRandomBeginEnd(first, second, rng);

	std::swap(cities[first], cities[second]);
	calculateFitness();
}

void Creature::mutateInv(std::mt19937& rng)
{
	size_t begin, end;
	getRandomBeginEnd(begin, end, rng);

	std::reverse(cities.begin() + begin, cities.begin() + end);
	calculateFitness();
}

Creature Creature::crossoverOX(Creature& other, std::mt19937& rng)
{
	size_t begin, end;
	getRandomBeginEnd(begin, end, rng);

	//std::vector<int> subVector(cities.begin() + i, cities.begin() + j);
	std::vector<int> newOrder(citiesCount, -1);

	std::set<int> ordered;

	for (size_t index = begin; index < end; index++)
	{
		newOrder[index] = cities[index];
		ordered.insert(cities[index]);
	}

	size_t i = 0;
	auto it = other.cities.begin();
	while (i<citiesCount)
	{
		if (newOrder[i] == -1)//empty
		{
			while (ordered.find(*it) != ordered.end())it++;
			newOrder[i] = *it;
			it++;
		}
		i++;
	}


	auto result = Creature(distanceMatrix, newOrder);
	return result;
}

std::vector<Creature> Creature::crossoverPMX(Creature& other, std::mt19937& rng)
{
	size_t begin, end;
	getRandomBeginEnd(begin, end, rng);

	//auto subSet1 = std::vector<int>(cities.begin() + begin, cities.begin() + end);
	//auto subSet2 = std::vector<int>(other.cities.begin() + begin, other.cities.begin() + end);

	auto newOrder1 = std::vector<int>(citiesCount, -1);
	auto newOrder2 = std::vector<int>(citiesCount, -1);

	for (size_t i = begin; i < end; i++)
	{
		newOrder1[i] = cities[i];
		newOrder2[i] = other.cities[i];
	}

	std::set<int> set;
	std::vector<int> randomSource;

	//this
	for (size_t i = 0; i < citiesCount; i++)
		set.insert(set.end(), i);
	for (size_t i = begin; i < end; i++)
		set.erase(cities[i]);

	randomSource = std::vector<int>(set.begin(), set.end());
	std::shuffle(randomSource.begin(), randomSource.end(), rng);
	size_t it = 0;
	while (!randomSource.empty())
	{
		while (newOrder1[it] != -1)//skip filled
			it++;
		newOrder1[it] = randomSource.back();
		randomSource.pop_back();
	}

	//other
	set.clear();
	for (size_t i = 0; i < citiesCount; i++)
		set.insert(set.end(), i);
	for (size_t i = begin; i < end; i++)
		set.erase(other.cities[i]);
	randomSource.clear();
	randomSource = std::vector<int>(set.begin(), set.end());
	std::shuffle(randomSource.begin(), randomSource.end(), rng);
	it = 0;
	while (!randomSource.empty())
	{
		while (newOrder2[it] != -1)//skip filled
			it++;
		newOrder2[it] = randomSource.back();
		randomSource.pop_back();
	}

	return { {distanceMatrix, newOrder1},
			{distanceMatrix, newOrder2} };
}

unsigned long int Creature::getHash() const
{
	return hash;
}

void Creature::calculateFitness()
{
	float fitness = 0.f;
	size_t i = 1;
	while (i < cities.size())
	{
		fitness += distanceMatrix->getDistance(cities[i], cities[i - 1]);
		i++;
	}
	fitness += distanceMatrix->getDistance(*cities.begin(), *(cities.end() - 1));
	this->fitness = fitness;

	//calculate hash;

	//std::hash<std::vector<size_t>>;
}

float Creature::getFitness() const
{
	return fitness;
}

std::string Creature::getInfo(bool extended) const
{
	std::stringstream ss;
	if (extended)
	{
		ss << "Creature Info: Cities: ";
		for (auto x : cities)
			ss << x << ", ";
		ss << cities[0];
	}
	ss << " Fitness: " << fitness;
	ss << std::endl;
	return ss.str();
}

std::vector<Creature> Creature::getPointNeighbors(size_t point) const
{
	std::vector<Creature> neighbors;

	for (size_t i = 0; i < citiesCount; i++)
	{
		if (i != point)//OPTIMIZE
		{
			auto c = Creature(*this);
			std::swap(c.cities[i], c.cities[point]);
			neighbors.push_back(c);
		}
	}
}

void Creature::getRandomBeginEnd(size_t& begin, size_t& end, std::mt19937& rng)
{
	begin = dist(rng);
	do
	{
		end = dist(rng);
	} while (begin == end);

	if (begin > end)
		std::swap(begin, end);
}

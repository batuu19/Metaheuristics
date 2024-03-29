#include "Creature.h"

Creature::Creature(DistanceMatrix* distanceMatrix, const std::vector<int>& cities)//private?
	:
	citiesCount(cities.size()),
	dist(0, citiesCount - 1),
	distanceMatrix(distanceMatrix)
{
	this->cities = new int[citiesCount];

	for (size_t i = 0; i < citiesCount; i++)
		this->cities[i] = cities[i];

	calculateFitness();//needed,optimize?
}

Creature::Creature(DistanceMatrix* distanceMatrix)
	:
	citiesCount(distanceMatrix->getSize()),
	distanceMatrix(distanceMatrix),
	dist(0, citiesCount - 1)
{
	//no cities yet, do not calculate fitness
	cities = new int[citiesCount];
}

Creature::Creature(const Creature& other)
	:
	citiesCount(other.citiesCount),
	dist(0, citiesCount - 1),
	distanceMatrix(other.distanceMatrix),
	fitness(other.fitness),
	hash(other.hash)
{
	cities = new int[citiesCount];
	for (size_t i = 0; i < citiesCount; i++)
	{
		cities[i] = other.cities[i];
	}
}

Creature::Creature(Creature&& other) noexcept
	:
	citiesCount(other.citiesCount),
	cities(other.cities),
	dist(std::move(other.dist)),
	distanceMatrix(other.distanceMatrix),
	fitness(other.fitness),
	hash(other.hash)
{
	other.cities = nullptr;
}

Creature& Creature::operator=(const Creature& other)
{
	this->citiesCount = other.citiesCount;
	//delete this->cities;
	//cities = new int[citiesCount];
	for (size_t i = 0; i < citiesCount; i++)
	{
		cities[i] = other.cities[i];
	}

	this->dist = std::uniform_int_distribution<size_t>(0, citiesCount - 1);//???
	this->distanceMatrix = other.distanceMatrix;
	this->fitness = other.fitness;
	this->hash = other.hash;
	return *this;
}

Creature& Creature::operator=(Creature&& other) noexcept
{
	this->citiesCount = other.citiesCount;
	this->fitness = other.fitness;
	this->hash = other.hash;

	delete this->cities;
	this->cities = other.cities;
	other.cities = nullptr;

	this->dist = std::move(other.dist);

	this->distanceMatrix = other.distanceMatrix;
	return *this;
}

Creature::~Creature()
{
	delete cities;
}

void Creature::init(std::mt19937& rng, bool greedy)
{
	if (greedy)
	{
		std::uniform_int_distribution<int> cityDist(0, citiesCount - 1);

		int city = cityDist(rng);

		std::vector<int> allCities(citiesCount);
		std::iota(allCities.begin(), allCities.end(), 0);
		allCities.erase(allCities.begin() + city);//they are 0,1,2,3 so this will erase right
		cities[0] = city;

		for (size_t i = 1; i < citiesCount; i++)
		{
			std::sort(allCities.begin(), allCities.end(), [this, &city](int c1, int c2) {
				return
					distanceMatrix->getDistance(city, c1) < distanceMatrix->getDistance(city, c2);
				});
			city = allCities[0];
			cities[i] = city;
			std::swap(*allCities.begin(), *allCities.rbegin());
			allCities.pop_back();
		}
	}
	else
	{
		std::iota(cities, cities + citiesCount, 0);//0,1,2,3,...
		std::shuffle(cities, cities + citiesCount, rng);
	}
	calculateFitness();
}

void Creature::mutateSwap(std::mt19937& rng)
{
	size_t first, second;
	getRandomBeginEnd(first, second, rng);
	mutateSwap(first, second);
}

void Creature::mutateSwap(size_t first, size_t second)
{
	std::swap(cities[first], cities[second]);
	calculateFitness();
}

void Creature::mutateSwap(std::mt19937& rng, size_t swapCount)
{
	size_t first, second;

	if (swapCount > citiesCount / 6)
	{
		for (size_t i = 0; i < swapCount; i++)
		{
			getRandomBeginEnd(first, second, rng);
			mutateSwap(first, second);
		}
	}
	else
	{
		while (swapCount > 1)
		{
			do
			{
				first = dist(rng);
				second = dist(rng);
			} while (
				citiesCount - second < 2 * swapCount ||
				(int)second - (int)first < 2 * (int)swapCount
				);
			std::swap_ranges(cities + first, cities + first + swapCount, cities + second);

			swapCount /= 2;
		}
		calculateFitness();
	}
}


void Creature::mutateInv(std::mt19937& rng)
{
	size_t begin, end;
	getRandomBeginEnd(begin, end, rng);

	std::reverse(cities + begin, cities + end);
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
	auto it = other.cities;
	while (i < citiesCount)
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

Creature Creature::crossoverPMX(Creature& other, std::mt19937& rng)
{
	size_t begin, end;
	getRandomBeginEnd(begin, end, rng);

	std::vector<int> newOrder(citiesCount, -1);
	std::vector<int> swatch(cities + begin, cities + end);//initial swatch of p1 in child
	for (size_t index = begin; index < end; index++)
	{
		newOrder[index] = cities[index];
	}
	std::sort(swatch.begin(), swatch.end());
	//find value in swatch of p2 that isn't in the child
	int nextVal = 0;
	int tVal = nextVal;
	size_t index = begin;
	while (index < end)
	{
		if (std::binary_search(swatch.begin(), swatch.end(), other.cities[index]))
			//if (swatch.contains(other.cities[index]))
			index++;
		else //found in parent 2
		{
			nextVal = other.cities[index];
			int tIndex = index;
			index++;
			do
			{
				tVal = cities[tIndex];
				auto tPtr = std::find(other.cities, other.cities + citiesCount, tVal);
				tIndex = tPtr - other.cities;
			} while (tIndex >= begin && tIndex < end);
			newOrder[tIndex] = nextVal;
		}
	}

	for (size_t i = 0; i < citiesCount; i++)
	{
		//optimize?
		if (newOrder[i] == -1)
			newOrder[i] = other.cities[i];
	}

	return Creature(distanceMatrix, newOrder);
}

const int* Creature::getCities() const
{
	return cities;
}

unsigned long long Creature::getHash() const
{
	return hash;
}

Creature Creature::getRandomCreature(const Problem& problem, std::mt19937& rng)
{
	std::vector<int> vec(problem.getDimension());
	std::iota(vec.begin(), vec.end(), 0);
	std::shuffle(vec.begin(), vec.end(), rng);
	return Creature(problem.getDistanceMatrix(), vec);
}

void Creature::calculateFitness()
{
	float fitness = 0.f;
	size_t i = 1;
	while (i < citiesCount)
	{
		fitness += distanceMatrix->getDistance(cities[i], cities[i - 1]);
		i++;
	}
	fitness += distanceMatrix->getDistance(cities[0], cities[citiesCount - 1]);
	this->fitness = fitness;

	hash = 0;
	//calculate hash;
	for (size_t i = 0; i < citiesCount; i++)
	{
		hash += static_cast<unsigned long long>(primes[i])*
			static_cast<unsigned long long>(cities[i]);
	}


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
		for (size_t i = 0; i < citiesCount; i++)
		{
			ss << cities[i] << ", ";
		}
		ss << cities[0];
	}
	ss << " Fitness: " << fitness;
	ss << std::endl;
	return ss.str();
}

std::vector<Creature> Creature::getRandomNeighbors(std::mt19937& rng, size_t count) const
{
	std::vector<Creature> neighbors;
	neighbors.reserve(count);
	std::uniform_int_distribution<int> swapDist(0, citiesCount - 1);
	size_t first, second;
	for (size_t i = 0; i < count; i++)
	{
		auto c = Creature(*this);
		getRandomBeginEnd(first, second, rng);
		c.mutateSwap(first, second);
		neighbors.push_back(c);
	}

	return neighbors;
}

std::vector<Creature> Creature::getPointNeighbors(size_t point) const
{
	std::vector<Creature> neighbors;
	neighbors.reserve(citiesCount);
	for (size_t i = 0; i < citiesCount; i++)
	{
		if (i != point)//OPTIMIZE
		{
			auto c = Creature(*this);
			std::swap(c.cities[i], c.cities[point]);
			c.calculateFitness();
			neighbors.push_back(c);
		}
	}
	return neighbors;
}

std::vector<Creature> Creature::getAllNeighbors() const
{
	std::vector<Creature> neighbors;
	neighbors.reserve(citiesCount * citiesCount);
	std::vector<Creature> temp;
	for (size_t i = 0; i < citiesCount; i++)
	{
		for (size_t j = i + 1; j < citiesCount; j++)
		{
			auto c = Creature(*this);
			c.mutateSwap(i, j);
			neighbors.push_back(c);
		}
	}

	return neighbors;
}

std::vector<Creature> Creature::getInvNeighbors(std::mt19937 & rng, size_t count) const
{
	std::vector<Creature> neighbors;
	neighbors.reserve(citiesCount);
	for (size_t i = 0; i < citiesCount; i++)
	{
		auto c = Creature(*this);
		c.mutateInv(rng);
		c.calculateFitness();
		neighbors.push_back(c);
	}
	return neighbors;
}

void Creature::getRandomBeginEnd(size_t& begin, size_t& end, std::mt19937& rng) const
{
	begin = dist(rng);
	do
	{
		end = dist(rng);
	} while (begin == end);

	if (begin > end)
		std::swap(begin, end);
}

bool Creature::operator<(const Creature& other) const
{
	return this->fitness < other.fitness;
}

bool Creature::operator<=(const Creature& other) const
{
	return this->fitness <= other.fitness;
}

bool Creature::operator>(const Creature& other) const
{
	return this->fitness > other.fitness;
}

bool Creature::operator>=(const Creature& other) const
{
	return this->fitness >= other.fitness;
}

//bool Creature::operator==(const Creature &other) const
//{
//    return this->fitness == other.fitness;
//}
#include "GreedyAlgorithm.h"

float GreedyAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");

	pop.init(rng, distanceMatrix);

	std::uniform_int_distribution<int> cityDist(0, citiesCount - 1);
	int city = cityDist(rng);
	int nextCity;
	std::vector<int> cities;
	std::vector<int> allCities(citiesCount);
	std::iota(allCities.begin(), allCities.end(), 0);
	allCities.erase(allCities.begin() + city);//they are 0,1,2,3 so this will erase right
	cities.reserve(citiesCount);
	cities.push_back(city);
	for (size_t i = 1; i < citiesCount; i++)
	{
		std::sort(allCities.begin(), allCities.end(), [this,&city](int c1, int c2) {
			return
				distanceMatrix->getDistance(city, c1) < distanceMatrix->getDistance(city, c2);
		});
		city = allCities[0];
		cities.push_back(city);
		std::swap(*allCities.begin(), *allCities.rbegin());
		allCities.pop_back();
	}

	Creature best = Creature(distanceMatrix, cities);
	csvFile << best.getFitness();
	csvFile.close();
	return best.getFitness();
	
}

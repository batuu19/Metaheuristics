#include "GreedyAlgorithm.h"

float GreedyAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");

	pop.init(rng, distanceMatrix);

	std::vector<int> cities;
	std::vector<int> allCities;
	std::vector<float> bests;
	int city;
	for(int cityIt = 0;cityIt<citiesCount;cityIt++)
	{
		city = cityIt;
		cities.clear();
		allCities = std::vector<int>(citiesCount);
		std::iota(allCities.begin(), allCities.end(), 0);
		allCities.erase(allCities.begin() + city);//they are 0,1,2,3 so this will erase right
		cities.reserve(citiesCount);
		cities.push_back(city);
		for (size_t i = 1; i < citiesCount; i++)
		{
			std::sort(allCities.begin(), allCities.end(), [this, &city](int c1, int c2) {
				return
					distanceMatrix->getDistance(city, c1) < distanceMatrix->getDistance(city, c2);
			});
			city = allCities[0];
			cities.push_back(city);
			std::swap(*allCities.begin(), *allCities.rbegin());
			allCities.pop_back();
		}
		bests.push_back(Creature(distanceMatrix,cities).getFitness());
	}
	auto best = *std::min(bests.begin(),bests.end());
	csvFile << best;
	csvFile.close();
	return best;
	
}

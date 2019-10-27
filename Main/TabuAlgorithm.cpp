#include "TabuAlgorithm.h"

TabuAlgorithm::TabuAlgorithm(const Problem &problem)
        :
        best(problem.getDistanceMatrix()),
        citiesCount(problem.getDimension())
{
}

void TabuAlgorithm::run(std::mt19937 &rng)
{
	//csv file
	std::ofstream csvFile;
	csvFile.open("tabu.csv");
	csvFile << "generation,best,bestEver\n";
	//csv file
    best.init(rng);

    auto bestFitness = best.getFitness();
    auto pairComp = [](const NeighborAndSwap& nas1,const NeighborAndSwap& nas2)
    {
        return nas1.first.getFitness() < nas2.first.getFitness();
    };
    std::uniform_int_distribution<size_t> pointDist(0, citiesCount-1);
    std::vector<NeighborAndSwap> neighborsAndSwaps;
    std::set<NeighborAndSwap, decltype(pairComp)> sorted(pairComp);

    std::stack<swap_t> swapsHistory;
	size_t generation = 0;
    while (swapsHistory.size() < MAX_SWAPS_HISTORY)//check if no improvement
    {
        neighborsAndSwaps.clear();
        sorted.clear();

        //neighborsAndSwaps = best.getPointNeighborsAndSwaps(pointDist(rng));
		//neighborsAndSwaps = best.getRandomNeighborsAndSwaps(rng, NEIGHBORS_COUNT);
		neighborsAndSwaps = best.getAllNeighborsAndSwaps();
//        std::transform(neighborsAndSwaps.begin(),neighborsAndSwaps.end(),
//                       std::back_inserter(neighbors),
//                       [](const auto& pair){return pair.first;});

        sorted.insert(neighborsAndSwaps.begin(), neighborsAndSwaps.end());

        //maybe not remove, but put at back of the list
        std::remove_if(neighborsAndSwaps.begin(), neighborsAndSwaps.end(), [this](const NeighborAndSwap &n)
        { return tabuList.contains(n.first); });


//      auto index = std::binary_search(neighbors.begin(), neighbors.end(), best, comp);
        if (!swapsHistory.empty() &&
                (neighborsAndSwaps.empty() || neighborsAndSwaps[0].first.getFitness() >= best.getFitness())
                )
        {
            //swap back
            //remove from history
            auto lastSwap = swapsHistory.top();
            swapsHistory.pop();
			tabuList.push(best);
            best.mutateSwap(lastSwap.second,lastSwap.first);
        }
        else
        {
            auto bestNeighbor = neighborsAndSwaps[0];
            swapsHistory.push(bestNeighbor.second);
			tabuList.push(best);
            best = bestNeighbor.first;
            bestFitness = std::min(bestFitness,best.getFitness());

        }
		csvFile << generation << "," << best.getFitness() << "," << bestFitness << std::endl;
        std::cout << "best: " << best.getFitness() <<"\tBEST_EVER"<<bestFitness<<std::endl;
		generation++;
    }
    std::cout << "BEST: " << bestFitness<< std::endl;
}

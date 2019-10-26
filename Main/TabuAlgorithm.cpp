#include "TabuAlgorithm.h"

TabuAlgorithm::TabuAlgorithm(const Problem &problem)
        :
        best(problem.getDistanceMatrix()),
        citiesCount(problem.getDimension())
{
}

void TabuAlgorithm::run(std::mt19937 &rng)
{
    best.init(rng);

    auto bestFitness = best.getFitness();
    auto pairComp = [](const NeighborAndSwap& nas1,const NeighborAndSwap& nas2)
    {
        return nas1.first.getFitness() < nas2.first.getFitness();
    };
    std::uniform_int_distribution<size_t> pointDist(0, citiesCount);
    std::vector<NeighborAndSwap> neighborsAndSwaps;
    std::set<NeighborAndSwap, decltype(pairComp)> sorted(pairComp);

    std::stack<swap_t> swapsHistory;

    while (swapsHistory.size() < 10)//check if no improvement
    {
        neighborsAndSwaps.clear();
        sorted.clear();

        neighborsAndSwaps = best.getPointNeighborsAndSwaps(pointDist(rng));
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
            best.mutateSwap(lastSwap.second,lastSwap.first);
        }
        else
        {
            auto bestNeighbor = neighborsAndSwaps[0];
            swapsHistory.push(bestNeighbor.second);
            best = bestNeighbor.first;
            bestFitness = std::min(bestFitness,best.getFitness());
        }

        std::cout << "best: " << best.getFitness() << std::endl;
    }
    std::cout << "BEST: " << bestFitness<< std::endl;
}

bool TabuAlgorithm::endCondition()
{
    return false;
}

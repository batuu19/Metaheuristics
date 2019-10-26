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

    std::uniform_int_distribution<size_t> pointDist(0, citiesCount);
    std::vector<NeighborAndSwap> neighborsAndSwaps;
    std::set<NeighborAndSwap> sorted;

    std::stack<swap_t> swaps;


    while (!endCondition())//check if no improvement
    {
        neighborsAndSwaps.clear();
        sorted.clear();

        neighborsAndSwaps = best.getPointNeighborsAndSwaps(pointDist(rng));
//        std::transform(neighborsAndSwaps.begin(),neighborsAndSwaps.end(),
//                       std::back_inserter(neighbors),
//                       [](const auto& pair){return pair.first;});
        auto comp = [](const Creature &c1, const Creature &c2)
        {
            return c1.getFitness() < c2.getFitness();
        };
        auto pairComp = [&comp](const NeighborAndSwap& nas1,const NeighborAndSwap& nas2)
        {
            return comp(nas1.first,nas2.first);
        };
        sorted = std::set<NeighborAndSwap>(neighborsAndSwaps.begin(), neighborsAndSwaps.end());

        //maybe not remove, but put at back of the list
        std::remove_if(neighborsAndSwaps.begin(), neighborsAndSwaps.end(), [this](const NeighborAndSwap &n)
        { return tabuList.contains(n.first); });


//      auto index = std::binary_search(neighbors.begin(), neighbors.end(), best, comp);
        auto bestNeighbor = neighborsAndSwaps[0];
        if (bestNeighbor.first.getFitness() >= best.getFitness())
        {
            //what to do here?
        }
        swaps.push(bestNeighbor.second);
        best = bestNeighbor.first;
        bestFitness = std::min(bestFitness,best.getFitness());

        std::cout << "best: " << best.getFitness() << std::endl;
    }
    std::cout << "BEST: " << best.getFitness() << std::endl;
}

bool TabuAlgorithm::endCondition()
{
    return false;
}

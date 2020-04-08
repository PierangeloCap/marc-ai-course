#ifndef HAMILTONIANCYCLE_H
#define HAMILTONIANCYCLE_H

#include <Modeling/RandomExplorationProblem.h>
#include <Modeling/HeuristicDrivenSearchProblem.h>
#include "GraphDimensionType.h"

using Graph = std::map<unsigned int, std::vector<unsigned int>>;

class HamiltonianCycle : public Modeling::RandomExplorationProblem, public Modeling::HeuristicDrivenSearchProblem {

public:
    double heuristic(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    std::shared_ptr<Modeling::State> getRandomState() const override; // Required by inheritance contract

    bool objectiveTest(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    bool areAdjacent(const unsigned int v, const unsigned int u) const; // Additional property

    unsigned int countNodes() const; // Additional property

    explicit HamiltonianCycle(const GraphDimensionType& dim);


};



#endif //HAMILTONIANCYCLE_H

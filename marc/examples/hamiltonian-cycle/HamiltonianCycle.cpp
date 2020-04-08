#include <cassert>
#include <cmath>
#include <algorithm>
#include <random>
#include "HamiltonianCycle.h"
#include "HamiltonianCycleState.h"

double HamiltonianCycle::heuristic(const std::shared_ptr<Modeling::State> &s) const {
    // Note 1. Downcasting is needed here (general State type to this Problem's State type)
    auto hcState = std::dynamic_pointer_cast<HamiltonianCycleState>(s); 
    auto vec = hcState->getValue();
    double badness = 0;
    for (unsigned int i = 0; i < vec.size()-1; i++) {
        if (!this->areAdjacent(vec.at(i), vec.at(i+1))) badness++;
    }
    if (!this->areAdjacent(vec.at(vec.size()-1), vec.at(0))) badness++;
    // Note 2. Very simple heuristic: square of number of "out-of-place" nodes
    return pow(badness, 2);
}

std::shared_ptr<Modeling::State> HamiltonianCycle::getRandomState() const {
    unsigned int nodes = this->countNodes();
    auto arr = std::make_unique<std::vector<unsigned int>>();
    for (unsigned int i = 1; i <= nodes; i++) arr->push_back(i);
    std::random_device rd;
    std::shuffle(arr->begin(), arr->end(), rd); // Note 3. Generate a random permutation of nodes
    return std::make_shared<HamiltonianCycleState>(std::move(arr));
}

bool HamiltonianCycle::objectiveTest(const std::shared_ptr<Modeling::State> &s) const {
    return this->trustedHeuristic(s) == 0; // Note 4. Objective Test is always trivial if heuristic is defined
}

bool HamiltonianCycle::areAdjacent(const unsigned int v, const unsigned int u) const {
    assert(v > 0 && u > 0 && v <= this->countNodes() && u <= this->countNodes());
    auto graphDim = dynamic_cast<const GraphDimensionType&>(this->Problem::getDim());
    auto adj = graphDim.getDim().at(v);
    return std::find(adj.begin(), adj.end(), u) != adj.end();
}

unsigned int HamiltonianCycle::countNodes() const {
    auto graphDim = dynamic_cast<const GraphDimensionType&>(this->Problem::getDim());
    return graphDim.getDim().size();
}

HamiltonianCycle::HamiltonianCycle(const GraphDimensionType &dim)
        : Modeling::RandomExplorationProblem(std::make_unique<GraphDimensionType>(dim.getDim())),
          Modeling::HeuristicDrivenSearchProblem(std::make_unique<GraphDimensionType>(dim.getDim())),
          Modeling::Problem(std::make_unique<GraphDimensionType>(dim.getDim())) { }


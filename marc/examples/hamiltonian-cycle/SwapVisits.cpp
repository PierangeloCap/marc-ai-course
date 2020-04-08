#include "SwapVisits.h"
#include "HamiltonianCycleState.h"

bool SwapVisits::satisfiesPreconditions(const std::shared_ptr<Modeling::State> &s) const {
    return true; // Note 1. It's always possible to swap two nodes (you just need to structurally ensure that from and to are legal...)
}

std::shared_ptr<Modeling::State> SwapVisits::evaluateEffects(const std::shared_ptr<Modeling::State> &s) const {
    auto hcState = std::dynamic_pointer_cast<HamiltonianCycleState>(s); // Note 2. Downcasting here is needed (general State type to HamiltonianCycleState)
    auto vec = hcState->getValue();
    unsigned int first = vec.at(this->from);
    vec.at(this->from) = vec.at(this->to);
    vec.at(this->to) = first; // Note 3. Perform a simple swap on a vector
    return std::make_shared<HamiltonianCycleState>(std::make_unique<std::vector<unsigned int>>(vec)); // Note 4. Return a new State
}

double SwapVisits::cost(const std::shared_ptr<Modeling::State> &s) const {
    return 0; // Note 5. Cost isn't really relevant in this case
}

SwapVisits::SwapVisits(unsigned int from, unsigned int to, std::string description) : from(from), to(to), Action(std::move(description)) { }

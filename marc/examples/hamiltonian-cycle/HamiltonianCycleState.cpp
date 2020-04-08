#include "HamiltonianCycleState.h"

void HamiltonianCycleState::print() const {
    auto arr = this->getValue();
    std::cout << "[" << arr.at(0);
    for (unsigned int i = 1; i < arr.size(); i++) {
        std::cout << ", " << arr.at(i);
    }
    std::cout << "]\n";
}

HamiltonianCycleState::HamiltonianCycleState(std::unique_ptr<std::vector<unsigned int>> val) : GenericState(std::move(val)) { }

#include "../../header/Modeling/StateSolution.h"

namespace Modeling {

    const std::weak_ptr<Solution> StateSolution::getSolution() const {
        return this->getRoleX();
    }

    const std::weak_ptr<State> StateSolution::getState() const {
        return this->getRoleY();
    }

    StateSolution::StateSolution(std::shared_ptr<Solution> sol, std::shared_ptr<State> state)
        : SingleOwnerAssociationLink(std::move(sol), std::move(state)) { }

}
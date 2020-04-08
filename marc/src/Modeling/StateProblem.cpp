#include "../../header/Modeling/StateProblem.h"

namespace Modeling {

    const std::weak_ptr<State> StateProblem::getState() const {
        return this->getRoleX();
    }

    const std::weak_ptr<Problem> StateProblem::getProblem() const {
        return this->getRoleY();
    }

    StateProblem::StateProblem(std::shared_ptr<State> state, std::shared_ptr<Problem> prob)
        : SingleOwnerAssociationLink(std::move(state), std::move(prob)) { }

}
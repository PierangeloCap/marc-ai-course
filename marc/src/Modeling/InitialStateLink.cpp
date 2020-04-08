#include "../../header/Modeling/InitialStateLink.h"
#include "../../header/Modeling/InitialStateProblem.h"

namespace Modeling {

    const std::weak_ptr<InitialStateProblem> InitialStateLink::getProblem() const {
        return this->getRoleX();
    }

    const std::weak_ptr<State> InitialStateLink::getState() const {
        return this->getRoleY();
    }

    InitialStateLink::InitialStateLink(const std::shared_ptr<InitialStateProblem> &prob, const std::shared_ptr<State> &state)
        : SingleOwnerAssociationLink(prob, state) { }

}
#include "../../header/Modeling/ActionProblem.h"
#include "../../header/Modeling/Action.h"
#include "../../header/Modeling/Problem.h"

namespace Modeling {

    const std::weak_ptr<Action> ActionProblem::getAction() {
        return this->getRoleY();
    }

    const std::weak_ptr<Problem> ActionProblem::getProblem() {
        return this->getRoleX();
    }

    ActionProblem::ActionProblem(const std::shared_ptr<Problem>& prob, const std::shared_ptr<Action>& act)
        : SingleOwnerAssociationLink(prob, act) { }

}


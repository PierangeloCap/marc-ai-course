#include <unordered_set>
#include <memory>

#include "../../header/Modeling/Problem.h"
#include "../../header/Modeling/Action.h"
#include "../../header/Modeling/State.h"

#include "../../header/Utils/Exceptions/NullPointerException.h"
#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"


namespace Modeling {

    class ProblemDimensionType;

    bool Problem::trustedObjectiveTest(const std::shared_ptr<State>& s) const {
        if (s->getStateProblem().lock().get() != this) 
            throw ViolatedPreconditionsException("Problem", "objectiveTest");
        return this->objectiveTest(s);
    }
    
    std::shared_ptr<State> Problem::doAction(const std::shared_ptr<State>& s, const std::shared_ptr<Action>& a) const {
        return a->trustedEvaluateEffects(s);
    }

    std::unordered_set<std::shared_ptr<Action>> Problem::getPossibleActions(const std::shared_ptr<State>& s) const {
        std::unordered_set<std::shared_ptr<Action>> result;
        std::shared_ptr<Action> act;
        for (auto itr = this->cbeginLinks(); itr != this->cendLinks(); itr++) {
            act = (*itr)->getAction().lock();
            if (act->trustedSatisfiesPreconditions(s)) result.insert(act);
        }
        return result;
    }

    const ProblemDimensionType& Problem::getDim() const {
        return *(this->dim);
    }

    void Problem::addAction(const std::shared_ptr<ActionProblem>& actLink) {
        this->addLink(std::move(actLink));
    }

    Problem::Problem(std::unique_ptr<ProblemDimensionType> dim) {
        if (!dim) throw NullPointerException();
        this->dim = std::move(dim);
    }

}
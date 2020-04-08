#include <string>
#include <utility>
#include <memory>

#include "../../header/Modeling/Action.h"
#include "../../header/Modeling/State.h"
#include "../../header/Modeling/Problem.h"

#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"
#include "../../header/Utils/Exceptions/ImmutablePropertyException.h"

namespace Modeling {
    
    bool Action::trustedSatisfiesPreconditions(const std::shared_ptr<State>& s) const {
        try {
            if (this->getProblem().lock().get() != s->getStateProblem().lock().get()) 
                throw ViolatedPreconditionsException("Action", "satisfiesPreconditions");
            return this->satisfiesPreconditions(s);
        }
        catch(MultiplicityConstraintException& e) { 
            throw MultiplicityConstraintException("Action", "ActionProblem", this->countLinks());
        }
    }

    std::shared_ptr<State> Action::trustedEvaluateEffects(const std::shared_ptr<State>& s) const {
        std::shared_ptr<State> result = this->evaluateEffects(s);
        try {
            auto resProblem = result->getStateProblem().lock();
            auto thisProblem = this->getProblem().lock();
            if (thisProblem.get() != resProblem.get()) 
                throw ViolatedPreconditionsException("Action", "evaluateEffects");
        }
        catch(MultiplicityConstraintException& e) { 
            auto thisProblem = this->getProblem().lock();
            result->setStateProblem(thisProblem);
        }
        return result;
    }

    double Action::trustedCost(const std::shared_ptr<State>& s) const {
        try {
            if (this->getProblem().lock().get() != s->getStateProblem().lock().get()) 
                throw ViolatedPreconditionsException("Action", "cost");
            return this->cost(s);
        }
        catch(MultiplicityConstraintException& e) { 
            throw MultiplicityConstraintException("Action", "ActionProblem", this->countLinks());
        }
    }

    const std::string Action::getDescription() const {
        return this->description;
    }

    const std::weak_ptr<Problem> Action::getProblem() const {
        auto result = this->cbeginLinks();
        if (result == this->cendLinks()) 
            throw MultiplicityConstraintException("Action", "ActionProblem", this->countLinks());
        return (*result).lock()->getProblem();
    }

    void Action::setProblem(const std::shared_ptr<Problem>& probLink) {
        try {
            auto thisPtr = this->shared_from_this();
            auto link = std::make_shared<ActionProblem>(probLink, thisPtr);
            this->addLink(link);
            probLink->addAction(link);
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("Action", "actionProblem"); }
    }

    Action::Action(std::string description) : description(std::move(description)) { }

}
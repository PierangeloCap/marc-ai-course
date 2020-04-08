#include <memory>

#include "../../header/Modeling/Solution.h"
#include "../../header/Modeling/StateSolution.h"

#include "../../header/Utils/Exceptions/ImmutablePropertyException.h"

#include "../../include/MCPP/MultiplicityConstraintException.h"

namespace Modeling {

    const std::weak_ptr<Problem> Solution::getSolutionProblem() const {
        return (this->getStateSolution().lock())->getStateProblem();
    }
    
    const std::weak_ptr<State> Solution::getStateSolution() const {
        auto result = this->cbeginLinks();
        if (result == this->cendLinks()) 
            throw MultiplicityConstraintException("Solution", "solutionState", this->countLinks());
        return (*result)->getState();
    }

    void Solution::setStateSolution(std::shared_ptr<State> stateLink) {
        try {
            auto thisPtr = this->shared_from_this();
            auto link = std::make_shared<StateSolution>(thisPtr, stateLink);
            this->addLink(std::move(link));
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("Solution", "stateSolution"); }
    }

}
        
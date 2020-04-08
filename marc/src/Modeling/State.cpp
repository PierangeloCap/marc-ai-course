#include <memory>

#include "../../header/Modeling/State.h"
#include "../../header/Modeling/StateProblem.h"

#include "../../header/Utils/Exceptions/ImmutablePropertyException.h"

#include "../../include/MCPP/MultiplicityConstraintException.h"

namespace Modeling {

    const std::weak_ptr<Problem> State::getStateProblem() const { 
        auto result = this->cbeginLinks();
        if (result == this->cendLinks()) 
            throw MultiplicityConstraintException("State", "StateProblem", this->countLinks());
        return (*result)->getProblem();
    }

    void State::setStateProblem(std::shared_ptr<Problem> probLink) {
        try {
            auto thisPtr = this->shared_from_this();
            auto link = std::make_shared<StateProblem>(thisPtr, probLink);
            this->addLink(std::move(link));
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("State", "stateProblem"); }
    }

}
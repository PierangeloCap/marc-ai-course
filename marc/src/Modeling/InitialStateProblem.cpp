#include <memory>

#include "../../header/Modeling/InitialStateProblem.h"
#include "../../header/Modeling/State.h"
#include "../../header/Modeling/ProblemDimensionType.h"
#include "../../header/Modeling/InitialStateLink.h"

#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"
#include "../../header/Utils/Exceptions/ImmutablePropertyException.h"

namespace Modeling {

    const std::weak_ptr<State> Modeling::InitialStateProblem::getInitialState() const {
        auto itr = this->StrongAssociationRole<InitialStateLink, 1, 1>::cbeginLinks();
        if (itr == this->StrongAssociationRole<InitialStateLink, 1, 1>::cendLinks()) 
            throw MultiplicityConstraintException("InitialStateProblem", "initState", 
                this->StrongAssociationRole<InitialStateLink, 1, 1>::countLinks());
        return (*itr)->getState();
    }

    void InitialStateProblem::setInitialState(const std::shared_ptr<State> &init) {
        if (init->getStateProblem().lock().get() != this) 
            throw ViolatedPreconditionsException("InitialStateProblem", "setInitialState"); //enforce 0..1 multiplicity constraint for State
        if (this->StrongAssociationRole<InitialStateLink, 1, 1>::countLinks() > 0) {
            auto itr = this->StrongAssociationRole<InitialStateLink, 1, 1>::cbeginLinks();
            this->StrongAssociationRole<InitialStateLink, 1, 1>::remove(*itr);
        }
        auto thisPtr = this->shared_from_this();
        auto nonConst = std::const_pointer_cast<InitialStateProblem>(thisPtr);
        auto link = std::make_shared<InitialStateLink>(nonConst, init);
        this->StrongAssociationRole<InitialStateLink, 1, 1>::addLink(std::move(link));  
        /*try {
            auto thisPtr = this->shared_from_this();
            auto nonConst = std::const_pointer_cast<InitialStateProblem>(thisPtr);
            auto link = std::make_shared<InitialStateLink>(nonConst, init);
            this->StrongAssociationRole<InitialStateLink, 1, 1>::addLink(std::move(link));
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("InitialStateProblem", "initState"); }*/
    }

    InitialStateProblem::InitialStateProblem(std::unique_ptr<ProblemDimensionType> dim) : Problem(std::move(dim)) { }

}
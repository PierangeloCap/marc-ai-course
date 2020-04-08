#ifndef INITIALSTATEPROBLEM_H
#define INITIALSTATEPROBLEM_H

#include <memory>

#include "Problem.h"

#include <StrongAssociationRole.h>

#include "../Utils/RunTimeTypeChecking/VirtualEnableSharedFromThis.h"

namespace Modeling {
    
    class ProblemDimensionType;
    
    class State;

    class InitialStateLink;

    class InitialStateProblem : public virtual Problem, protected StrongAssociationRole<InitialStateLink, 1, 1>,
                                public virtual_enable_shared_from_this<InitialStateProblem> {

    public:
        const std::weak_ptr<State> getInitialState() const;

        void setInitialState(const std::shared_ptr<State>& init);

        explicit InitialStateProblem(std::unique_ptr<ProblemDimensionType> dim);

    };

}

#endif /* INITIALSTATEPROBLEM_H */


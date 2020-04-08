#ifndef PROBLEM_H
#define PROBLEM_H

#include <limits>

#include <StrongAssociationRole.h>

#include "Action.h"
#include "ProblemDimensionType.h"

namespace Modeling {

    class State;

    class Problem : protected StrongAssociationRole<ActionProblem, 0, STAR> {

        friend void Action::setProblem(const std::shared_ptr<Problem>& probLink);

    protected:
        std::unique_ptr<ProblemDimensionType> dim;

        void addAction(const std::shared_ptr<ActionProblem>& actLink);

    public:
        virtual bool objectiveTest(const std::shared_ptr<State>& s) const = 0;

        bool trustedObjectiveTest(const std::shared_ptr<State>& s) const;

        virtual std::unordered_set<std::shared_ptr<Action>> getPossibleActions(const std::shared_ptr<State>& s) const;

        virtual std::shared_ptr<State> doAction(const std::shared_ptr<State>& s, const std::shared_ptr<Action>& a) const;

        const ProblemDimensionType& getDim() const;

        virtual ~Problem() = default;

        explicit Problem(std::unique_ptr<ProblemDimensionType> dim);


    };
    
}


#endif

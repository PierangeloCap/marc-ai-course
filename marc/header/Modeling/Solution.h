#ifndef SOLUTION_H
#define SOLUTION_H

#include <memory>

#include <StrongAssociationRole.h>

#include "State.h"

namespace Modeling {

    class Problem;

    class StateSolution;

    class Solution : protected StrongAssociationRole<StateSolution, 1, 1>, public std::enable_shared_from_this<Solution> {

    public:
        [[nodiscard]] const std::weak_ptr<Problem> getSolutionProblem() const;

        [[nodiscard]] const std::weak_ptr<State> getStateSolution() const;

        void setStateSolution(std::shared_ptr<State> stateLink);

        virtual bool operator==(const Solution& s) {
            return *(this->getStateSolution().lock()) == *(s.getStateSolution().lock());
        }

    };
    
}



#endif /* SOLUTION_H */


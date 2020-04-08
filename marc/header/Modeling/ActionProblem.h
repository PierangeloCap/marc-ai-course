#ifndef ACTIONPROBLEM_H
#define ACTIONPROBLEM_H

#include <SingleOwnerAssociationLink.h>

namespace Modeling {

    class Action;

    class Problem;

    class ActionProblem : protected SingleOwnerAssociationLink<Problem, Action> {

    public:
        const std::weak_ptr<Action> getAction();

        const std::weak_ptr<Problem> getProblem();

        ActionProblem(const std::shared_ptr<Problem>& prob, const std::shared_ptr<Action>& act);

    };

}


#endif // ACTIONPROBLEM_H

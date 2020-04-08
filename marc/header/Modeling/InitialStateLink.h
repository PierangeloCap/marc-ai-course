#ifndef INITIALSTATELINK_H
#define INITIALSTATELINK_H

#include <SingleOwnerAssociationLink.h>

namespace Modeling {

    class InitialStateProblem;

    class State;

    class InitialStateLink : protected SingleOwnerAssociationLink<InitialStateProblem, State> {

    public:
        [[nodiscard]] const std::weak_ptr<InitialStateProblem> getProblem() const;

        [[nodiscard]] const std::weak_ptr<State> getState() const;

        InitialStateLink(const std::shared_ptr<InitialStateProblem>& prob, const std::shared_ptr<State>& state);

    };

}


#endif //INITIALSTATELINK_H

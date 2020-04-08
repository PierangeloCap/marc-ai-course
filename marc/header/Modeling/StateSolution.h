#ifndef STATESOLUTION_H
#define STATESOLUTION_H

#include <SingleOwnerAssociationLink.h>

namespace Modeling {

    class Solution;

    class State;

    class StateSolution : protected SingleOwnerAssociationLink<Solution, State> {

    public:
        [[nodiscard]] const std::weak_ptr<Solution> getSolution() const;

        [[nodiscard]] const std::weak_ptr<State> getState() const;

        StateSolution(std::shared_ptr<Solution> sol, std::shared_ptr<State> state);

    };

}

#endif //STATESOLUTION_H

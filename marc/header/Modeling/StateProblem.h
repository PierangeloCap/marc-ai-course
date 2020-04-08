#ifndef STATEPROBLEM_H
#define STATEPROBLEM_H

#include <memory>
#include <SingleOwnerAssociationLink.h>

namespace Modeling {

    class State;

    class Problem;

    class StateProblem : protected SingleOwnerAssociationLink<State, Problem> {

    public:
        [[nodiscard]] const std::weak_ptr<State> getState() const;

        [[nodiscard]] const std::weak_ptr<Problem> getProblem() const;

        StateProblem(std::shared_ptr<State> state, std::shared_ptr<Problem> prob);

    };

}

#endif //STATEPROBLEM_H

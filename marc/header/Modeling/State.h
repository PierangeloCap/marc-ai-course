#ifndef STATE_H
#define STATE_H

#include <memory>
#include <StrongAssociationRole.h>

namespace Modeling {

    class Problem;

    class StateProblem;

    class State : protected StrongAssociationRole<StateProblem, 1, 1>, public std::enable_shared_from_this<State> {

    public:
        [[nodiscard]] const std::weak_ptr<Problem> getStateProblem() const;

        void setStateProblem(std::shared_ptr<Problem> probLink);

        virtual bool operator==(const State& s) = 0;

    };

}

#endif
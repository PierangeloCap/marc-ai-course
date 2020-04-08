#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <WeakAssociationRole.h>
#include "ActionProblem.h"

namespace Modeling {

    class State;

    class Action : protected WeakAssociationRole<ActionProblem, 1, 1>, public std::enable_shared_from_this<Action> {

    private:
        const std::string description;

    public:
        virtual bool satisfiesPreconditions(const std::shared_ptr<State>& s) const = 0;

        virtual std::shared_ptr<State> evaluateEffects(const std::shared_ptr<State>& s) const = 0;

        virtual double cost(const std::shared_ptr<State>& s) const = 0;

        bool trustedSatisfiesPreconditions(const std::shared_ptr<State>& s) const;

        std::shared_ptr<State> trustedEvaluateEffects(const std::shared_ptr<State>& s) const;

        double trustedCost(const std::shared_ptr<State>& s) const;

        const std::string getDescription() const;

        const std::weak_ptr<Problem> getProblem() const;

        void setProblem(const std::shared_ptr<Problem>& probLink);

        Action(std::string description);

        virtual ~Action() = default;

    };
    
}

#endif

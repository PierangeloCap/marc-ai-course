#ifndef RANDOMEXPLORATIONPROBLEM_H
#define RANDOMEXPLORATIONPROBLEM_H

#include <memory>
#include "Problem.h"

#include "../Utils/RunTimeTypeChecking/VirtualEnableSharedFromThis.h"

namespace Modeling {

    class State;

    class Action;

    class ProblemDimensionType;

    class RandomExplorationProblem : public virtual Problem, public virtual_enable_shared_from_this<RandomExplorationProblem> {

    public:
        virtual std::shared_ptr<State> getRandomState() const = 0;

        virtual std::shared_ptr<State> getRandomNeighbor(const std::shared_ptr<State>& s) const;

        virtual std::shared_ptr<Action> getRandomApplicableAction(const std::shared_ptr<State>& s) const;

        virtual std::shared_ptr<State> getBestRandomSampledNeighbor(unsigned int samples, const std::shared_ptr<State>& s) const;

        virtual std::shared_ptr<Action> getRandomBestAction(unsigned int samples, const std::shared_ptr<State>& s) const;

        std::shared_ptr<State> trustedGetRandomState() const;

        explicit RandomExplorationProblem(std::unique_ptr<ProblemDimensionType> dim);

    };
    
}


#endif /* RANDOMEXPLORATIONPROBLEM_H */


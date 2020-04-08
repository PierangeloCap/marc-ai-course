#ifndef HEURISTICDRIVENSEARCHPROBLEM_H
#define HEURISTICDRIVENSEARCHPROBLEM_H

#include "Problem.h"

namespace Modeling {
    
    class ProblemDimensionType;
    
    class State;

    class HeuristicDrivenSearchProblem : public virtual Problem {

    public:
        virtual double heuristic(const std::shared_ptr<State>& s) const = 0;

        double trustedHeuristic(const std::shared_ptr<State>& s) const;

        explicit HeuristicDrivenSearchProblem(std::unique_ptr<ProblemDimensionType> dim);

    };

    
}

#endif /* HEURISTICDRIVENSEARCHPROBLEM_H */


#ifndef OPTIMIZATIONPROBLEM_H
#define OPTIMIZATIONPROBLEM_H

#include <memory>
#include "Problem.h"

namespace Modeling {

    class Solution;

    enum direction { MIN, MAX };

    class OptimizationProblem : public virtual Problem {

    protected:
        direction optDirection;

    public:
        virtual double objectiveFunction(const std::shared_ptr<Solution>& sol) const = 0;

        double trustedObjectiveFunction(const std::shared_ptr<Solution>& sol) const;

        direction getDirection() const;

        void setDirection(direction optDirection);

        OptimizationProblem(std::unique_ptr<ProblemDimensionType> dim, direction optDirection);

    };
    
}



#endif /* OPTIMIZATIONPROBLEM_H */


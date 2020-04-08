#include <memory>
#include "../../header/Modeling/OptimizationProblem.h"
#include "../../header/Modeling/Solution.h"
#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"


namespace Modeling {
    
    double OptimizationProblem::trustedObjectiveFunction(const std::shared_ptr<Solution>& sol) const {
        if (sol->getSolutionProblem().lock().get() != this) 
            throw ViolatedPreconditionsException("OptimizationProblem", "objectiveFunction");
        return this->objectiveFunction(sol);
    }
    
    direction OptimizationProblem::getDirection() const {
        return this->optDirection;
    }
        
    void OptimizationProblem::setDirection(direction optDir) {
        this->optDirection = optDir;
    }

    OptimizationProblem::OptimizationProblem(std::unique_ptr<ProblemDimensionType> dim, direction optDirection) : Problem(std::move(dim)) {
        this->optDirection = optDirection;
    }
    
}
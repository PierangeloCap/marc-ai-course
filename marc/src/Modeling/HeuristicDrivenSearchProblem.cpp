#include <memory>
#include "../../header/Modeling/HeuristicDrivenSearchProblem.h"
#include "../../header/Modeling/State.h"
#include "../../header/Modeling/ProblemDimensionType.h"
#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"

namespace Modeling {

    double HeuristicDrivenSearchProblem::trustedHeuristic(const std::shared_ptr<State>& s) const {
        if (s->getStateProblem().lock().get() != this) 
        	throw ViolatedPreconditionsException("HeuristicDrivenSearchProblem", "heuristic");
        return this->heuristic(s);
    }

    HeuristicDrivenSearchProblem::HeuristicDrivenSearchProblem(std::unique_ptr<ProblemDimensionType> dim) : Problem(std::move(dim)) { }

}
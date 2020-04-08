#ifndef SEQUENTIALSOLVER_H
#define SEQUENTIALSOLVER_H

#include <memory>
#include "Solver.h"

namespace Modeling {
    
    class Solution;
    
    class Problem;
    
}

namespace Solving {
    
    class SequentialSolver : public Solver {
               
    public:
        virtual std::shared_ptr<Modeling::Solution> solve() const;
            
    };
    
    
}

#endif /* SEQUENTIALSOLVER_H */


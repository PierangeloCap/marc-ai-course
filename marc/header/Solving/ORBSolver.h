#ifndef ORBSOLVER_H
#define ORBSOLVER_H

#include "../../header/Solving/Solver.h"
#include "../../header/Modeling/HeuristicDrivenSearchProblem.h"
#include "../../header/Modeling/RandomExplorationProblem.h"
#include <vector>


namespace Modeling {

    class State;

}


namespace Solving {

    //ORB: Ordered Random Bootstrap
    class ORBSolver : public Solver { 

    private:
        mutable Modeling::HeuristicDrivenSearchProblem* heuristicCache = nullptr;

        mutable Modeling::RandomExplorationProblem* randCache = nullptr;

        unsigned int samples;

        std::vector<std::shared_ptr<Modeling::State>> sources;

        unsigned int findSourcePosition(const std::shared_ptr<Modeling::State>& state,
                                        unsigned int min, unsigned int max) const;

        std::shared_ptr<Modeling::State> getRandomState() const;

        double heuristic(const std::shared_ptr<Modeling::State>& state) const;
        
    public:
        void bootstrap();

        std::vector<std::shared_ptr<Modeling::State>> getBootstrap() const;

        void addBootstrapState(const std::shared_ptr<Modeling::State>& state);

        virtual std::shared_ptr<Modeling::Solution> solve() const;    

        ORBSolver(unsigned int samples);   

    };

}


#endif  /* ORBSOLVER_H */
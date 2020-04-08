#ifndef RESTARTUNTILGLOBALOPTIMUMSOLVER_H
#define RESTARTUNTILGLOBALOPTIMUMSOLVER_H

#include <memory>
#include <Solving/SequentialSolver.h>

class RestartUntilGlobalOptimumSolver : public Solving::SequentialSolver {

private:
    struct ExecData {
        unsigned int totIterations = 0;
        void addToIterations(const unsigned int x) {
            this->totIterations+=x;
        }
    };

    std::shared_ptr<ExecData> e = std::make_shared<ExecData>();

    const unsigned int restarts;

public:
    unsigned int getTotIterations() const;

    virtual std::shared_ptr<Modeling::Solution> solve() const; // Note 1. SequentialSolver::solve is redefined

    explicit RestartUntilGlobalOptimumSolver(const unsigned int res);

};


#endif //RESTARTUNTILGLOBALOPTIMUMSOLVER_H

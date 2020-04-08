#ifndef NQUEENS_H
#define NQUEENS_H

#include <Modeling/RandomExplorationProblem.h>
#include <Modeling/HeuristicDrivenSearchProblem.h>
#include <Modeling/InitialStateProblem.h>
#include <Modeling/ProblemDimensionType.h>


class IntDimensionType : public Modeling::ProblemDimensionType {

private:
    const unsigned int dim;

public:
    [[nodiscard]] const unsigned int getDim() const {
        return this->dim;
    }

    explicit IntDimensionType(unsigned int dim) : dim(std::move(dim)) { }

};


class NQueens : public Modeling::RandomExplorationProblem, 
                public Modeling::HeuristicDrivenSearchProblem,
                public Modeling::InitialStateProblem {

public:
    double heuristic(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    std::shared_ptr<Modeling::State> getRandomState() const override; // Required by inheritance contract

    bool objectiveTest(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    explicit NQueens(const unsigned int dim);

};


#endif /* NQUEENS_H */
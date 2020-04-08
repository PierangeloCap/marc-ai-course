#include "../header/NQueens.h"
#include "../header/QueensBoard.h"
#include <random>


double NQueens::heuristic(const std::shared_ptr<Modeling::State>& s) const {
    double res = 0.0;
    const unsigned int queens = dynamic_cast<const IntDimensionType&>(this->getDim()).getDim();
    // Note 1. Downcasting is needed here (general State type to this Problem's State type)
    auto board = std::dynamic_pointer_cast<QueensBoard>(s)->getValue(); 

    for (unsigned int i = 0; i < queens; i++) {
        for (unsigned int j = i+1; j < queens; j++) {
            if (board[i] == board[j] || (abs(board[j] - board[i]) == j - i)) res++;
        }
    }

    return res;

}

std::shared_ptr<Modeling::State> NQueens::getRandomState() const {
    const unsigned int queens = dynamic_cast<const IntDimensionType&>(this->getDim()).getDim();
    auto arr = std::make_unique<std::vector<unsigned int>>();
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, queens);

    for (unsigned int i = 0; i < queens; i++) arr->push_back(dist(rng));
    return std::make_shared<QueensBoard>(std::move(arr));
}

bool NQueens::objectiveTest(const std::shared_ptr<Modeling::State>& s) const {
    return this->heuristic(s) == 0; // Note 2. Objective Test is always trivial if heuristic is defined
}

NQueens::NQueens(const unsigned int dim) : 
    Modeling::RandomExplorationProblem(std::make_unique<IntDimensionType>(dim)),
    Modeling::HeuristicDrivenSearchProblem(std::make_unique<IntDimensionType>(dim)),
    Modeling::InitialStateProblem(std::make_unique<IntDimensionType>(dim)),
    Modeling::Problem(std::make_unique<IntDimensionType>(dim)) { }


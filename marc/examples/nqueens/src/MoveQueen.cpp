#include "../header/MoveQueen.h"
#include "../header/QueensBoard.h"
#include "../header/NQueens.h"


bool MoveQueen::satisfiesPreconditions(const std::shared_ptr<Modeling::State>& s) const {
    const unsigned int queens = dynamic_cast<const IntDimensionType&>(
        this->getProblem().lock()->getDim()
    ).getDim();
    auto board = std::dynamic_pointer_cast<QueensBoard>(s)->getValue(); 
    return board[this->pos] + squares < queens && board[pos] + squares >= 0;
} 

std::shared_ptr<Modeling::State> MoveQueen::evaluateEffects(const std::shared_ptr<Modeling::State>& s) const {
    auto board = std::dynamic_pointer_cast<QueensBoard>(s)->getValue(); 
    auto newBoard = std::make_unique<std::vector<unsigned int>>(board.begin(), board.end());
    *(newBoard->begin() + this->pos) += squares;
    return std::make_shared<QueensBoard>(std::move(newBoard));
}

double MoveQueen::cost(const std::shared_ptr<Modeling::State>& s) const {
    return 0.0;
}

MoveQueen::MoveQueen(unsigned int pos, unsigned int squares, std::string description) :
    pos(pos), squares(squares), Modeling::Action(std::move(description)) {}
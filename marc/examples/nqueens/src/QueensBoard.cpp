#include "../header/QueensBoard.h"
#include <vector>


void QueensBoard::print() const {
    auto arr = this->getValue();
    std::cout << "[" << arr.at(0);
    for (unsigned int i = 1; i < arr.size(); i++) {
        std::cout << ", " << arr.at(i);
    }
    std::cout << "]\n";
}


QueensBoard::QueensBoard(std::unique_ptr<std::vector<unsigned int>> val) : 
    GenericState(std::move(val)) { }


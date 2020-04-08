#ifndef MOVEQUEEN_H
#define MOVEQUEEN_H

#include <Modeling/Action.h>


class MoveQueen : public Modeling::Action {

private:
    const unsigned int pos; // Note 1. Additional Action parameters: need to be grounded to all possible values

    const unsigned int squares; 

public:
    bool satisfiesPreconditions(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    std::shared_ptr<Modeling::State> evaluateEffects(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    double cost(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    MoveQueen(unsigned int pos, unsigned int squares, std::string description);

};


#endif //MOVEQUEEN_H

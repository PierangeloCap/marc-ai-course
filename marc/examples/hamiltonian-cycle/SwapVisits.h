#ifndef SWAPVISITS_H
#define SWAPVISITS_H

#include <Modeling/Action.h>

class SwapVisits : public Modeling::Action {

private:
    const unsigned int from; // Note 1. Additional Action parameters: need to be grounded to all possible values

    const unsigned int to;

public:
    bool satisfiesPreconditions(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    std::shared_ptr<Modeling::State> evaluateEffects(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    double cost(const std::shared_ptr<Modeling::State>& s) const override; // Required by inheritance contract

    SwapVisits(unsigned int from, unsigned int to, std::string description);

};


#endif //SWAPVISITS_H

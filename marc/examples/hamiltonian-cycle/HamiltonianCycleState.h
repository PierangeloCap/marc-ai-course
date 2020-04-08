#ifndef HAMILTONIANCYCLESTATE_H
#define HAMILTONIANCYCLESTATE_H

#include <vector>
#include "Modeling/GenericState.h"

class HamiltonianCycleState : public Modeling::GenericState<std::vector<unsigned int>> {

public:
    void print() const; 

    explicit HamiltonianCycleState(std::unique_ptr<std::vector<unsigned int>> val);

 	//Note 1. We decided not to redefine operator== since std::vector has an efficient std definition for it
 	//        HamiltonianCycleState inherits operator== from GenericState
};


#endif //HAMILTONIANCYCLESTATE_H

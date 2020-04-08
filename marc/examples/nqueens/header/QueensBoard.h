#ifndef QUEENSBOARD_H
#define QUEENSBOARD_H

#include <Modeling/GenericState.h>
#include <vector>


class QueensBoard : public Modeling::GenericState<std::vector<unsigned int>> {

public:
    void print() const; 

 	/* 
     * Note:
 	 * We decided not to redefine operator== since std::vector has an efficient std definition for it
     * QueensBoard inherits operator== from GenericState
     */

    explicit QueensBoard(std::unique_ptr<std::vector<unsigned int>> val);

};



#endif /* QUEENSBOARD_H */
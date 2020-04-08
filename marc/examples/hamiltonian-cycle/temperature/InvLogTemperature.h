#ifndef INVLOGTEMPERATURE_H
#define INVLOGTEMPERATURE_H

#include "Solving/Algorithms/Temperature.h"

class InvLogTemperature : public Solving::Algorithms::Temperature {


public:
    unsigned int T0;

    const double alpha;

    double temperature(const unsigned int step) const override;

    explicit InvLogTemperature(unsigned int T0, const double alpha);


};


#endif //INVLOGTEMPERATURE_H

#ifndef EXPONENTIALTEMPERATURE_H
#define EXPONENTIALTEMPERATURE_H

#include "Solving/Algorithms/Temperature.h"

class ExponentialTemperature : public Solving::Algorithms::Temperature {

public:
    unsigned int T0;

    const unsigned int dim;

    const double alpha;

    double temperature(const unsigned int step) const override;

    explicit ExponentialTemperature(unsigned int T0, const double alpha, unsigned int dim);

};


#endif //EXPONENTIALTEMPERATURE_H

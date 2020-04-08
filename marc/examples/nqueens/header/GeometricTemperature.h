#ifndef GEOMETRICTEMPERATURE_H
#define GEOMETRICTEMPERATURE_H

#include "Solving/Algorithms/Temperature.h"

class GeometricTemperature : public Solving::Algorithms::Temperature {

public:
    unsigned int T0;

    const double alpha;

    double temperature(const unsigned int step) const override;

    explicit GeometricTemperature(unsigned int T0, const double alpha);

};


#endif //GEOMETRICTEMPERATURE_H

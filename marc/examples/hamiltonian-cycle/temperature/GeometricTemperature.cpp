#include <cmath>
#include "GeometricTemperature.h"

double GeometricTemperature::temperature(const unsigned int step) const {
    return pow(alpha, step-1)*T0;
}

GeometricTemperature::GeometricTemperature(unsigned int T0, const double alpha) : alpha(alpha), T0(T0) { }

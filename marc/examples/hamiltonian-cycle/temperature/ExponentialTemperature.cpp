#include <cmath>
#include "ExponentialTemperature.h"

double ExponentialTemperature::temperature(const unsigned int step) const {
    return T0*exp((-alpha)*pow(step-1, (double)1/dim));
}

ExponentialTemperature::ExponentialTemperature(unsigned int T0, const double alpha, unsigned int dim) : alpha(alpha), T0(T0), dim(dim) { }

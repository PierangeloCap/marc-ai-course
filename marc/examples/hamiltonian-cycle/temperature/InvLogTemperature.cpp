#include <cmath>
#include "InvLogTemperature.h"

double InvLogTemperature::temperature(const unsigned int step) const {
    return (alpha*T0)/(log(1+step));
}

InvLogTemperature::InvLogTemperature(unsigned int T0, const double alpha) : alpha(alpha), T0(T0) { }

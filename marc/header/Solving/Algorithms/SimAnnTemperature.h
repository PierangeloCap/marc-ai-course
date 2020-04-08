#ifndef SIMANNTEMPERATURE_H
#define SIMANNTEMPERATURE_H


#include <SingleOwnerAssociationLink.h>

namespace Solving::Algorithms {

    class SimulatedAnnealing;

    class Temperature;

    class SimAnnTemperature : protected SingleOwnerAssociationLink<SimulatedAnnealing, Temperature> {

    public:
        [[nodiscard]] const std::weak_ptr<SimulatedAnnealing> getSimulatedAnnealingInstance() const;

        [[nodiscard]] const std::weak_ptr<Temperature> getTemperatureFunctor() const;

        SimAnnTemperature(std::shared_ptr<SimulatedAnnealing> sim, std::shared_ptr<Temperature> temp);

    };

}


#endif //SIMANNTEMPERATURE_H

#include "../../../header/Solving/Algorithms/SimAnnTemperature.h"

namespace Solving {

    namespace Algorithms {

        const std::weak_ptr<SimulatedAnnealing> Solving::Algorithms::SimAnnTemperature::getSimulatedAnnealingInstance() const {
            return this->getRoleX();
        }

        const std::weak_ptr<Temperature> SimAnnTemperature::getTemperatureFunctor() const {
            return this->getRoleY();
        }

        SimAnnTemperature::SimAnnTemperature(std::shared_ptr<SimulatedAnnealing> sim, std::shared_ptr<Temperature> temp)
                : SingleOwnerAssociationLink(std::move(sim), std::move(temp)) { }

    }

}
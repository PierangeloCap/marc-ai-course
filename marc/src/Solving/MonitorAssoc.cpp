#include "../../header/Solving/MonitorAssoc.h"


namespace Solving {

    const std::weak_ptr<Solver> MonitorAssoc::getSolver() const {
        return this->getRoleX();
    }

    const std::weak_ptr<SolverMonitor> MonitorAssoc::getMonitor() const {
        return this->getRoleY();
    }

    void MonitorAssoc::setMonitor(std::shared_ptr<SolverMonitor> mon) {
        this->setRoleY(std::move(mon));
    }

    MonitorAssoc::MonitorAssoc(std::shared_ptr<Solver> sol, std::shared_ptr<SolverMonitor> mon) :
        SingleOwnerAssociationLink(std::move(sol), std::move(mon)) {}

}
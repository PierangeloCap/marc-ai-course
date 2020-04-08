#ifndef MONITORASSOC_H
#define MONITORASSOC_H

#include <SingleOwnerAssociationLink.h>
#include <memory>


namespace Solving {

    class Solver;

    class SolverMonitor;

    class MonitorAssoc : protected SingleOwnerAssociationLink<Solver, SolverMonitor> {

    public:
        [[nodiscard]] const std::weak_ptr<Solver> getSolver() const;

        [[nodiscard]] const std::weak_ptr<SolverMonitor> getMonitor() const;

        void setMonitor(std::shared_ptr<SolverMonitor> mon);

        MonitorAssoc(std::shared_ptr<Solver> sol, std::shared_ptr<SolverMonitor> mon);

    };

}


#endif /* MONITORASSOC_H */
#ifndef SOLVERMONITOR_H
#define SOLVERMONITOR_H

#include <string>
#include <chrono>


namespace Solving {

    class SolverMonitor {

    private:
        std::string name;

        std::chrono::system_clock::time_point restartTime;

        std::chrono::system_clock::time_point runStart;

    public:
        void begin() const;

        void logRunBegin(const unsigned int it, const unsigned int tot);

        void logRestartBegin(const unsigned int it, const unsigned int tot, const bool re);

        void logRestartCompletion(const std::string) const;

        void logRunCompletion() const;

        void failure(const std::string) const;

        void end() const;

        explicit SolverMonitor(std::string name);

    };

}





#endif /* SOLVERMONITOR_H */
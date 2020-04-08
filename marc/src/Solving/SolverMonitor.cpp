#include "../../header/Solving/SolverMonitor.h"
#include <iostream>
#include <iomanip>

namespace Solving {

    void SolverMonitor::begin() const {
        std::cout << "\n### MARC: calling " << this->name << " Solver" << std::endl;
    }

    void SolverMonitor::logRunBegin(const unsigned int it, const unsigned int tot) {
        this->restartTime = std::chrono::system_clock::now();
        std::cout << "\n> Running Algorithm " << (it+1) << "/" << tot << std::endl;
    }

    void SolverMonitor::logRestartBegin(const unsigned int it, const unsigned int tot, const bool re) {
        this->runStart = std::chrono::system_clock::now();
        std::cout << ">> Restart: " << (it+1) << "/" << tot << 
            "\n>>> Reinitialization: " << std::boolalpha << re <<
            "\n>>> Internal logs {" << std::endl;
    }

    void SolverMonitor::logRestartCompletion(const std::string res) const {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - this->runStart).count(); 
        std::cout << "}\n>> Restart completed. Results:\n>>> " << res << 
            "\n>>> Run time: " << std::fixed << std::setprecision(6) << (float)duration/(float)1e6 << "\n" << std::endl;
    }

    void SolverMonitor::logRunCompletion() const {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - this->restartTime).count(); 
        std::cout << "> Run time: " << std::fixed << std::setprecision(6) << (float)duration/(float)1e6 << "\n" << std::endl;
    }

    void SolverMonitor::failure(const std::string desc) const {
        std::cout << "<FATAL>: " << desc << "\n" << std::endl;
    }

    void SolverMonitor::end() const {
        std::cout << "Solver execution completed. ###\n" << std::endl;
    }

    SolverMonitor::SolverMonitor(std::string name) : name(name) {}

}
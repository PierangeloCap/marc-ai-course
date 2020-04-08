#ifndef NOAPPLICABLEACTIONEXCEPTION_H
#define NOAPPLICABLEACTIONEXCEPTION_H

#include <exception>

struct NoApplicableActionException : public std::exception {

    const char* what() const noexcept override {
        return "Algorithm encountered a sink State - search cannot continue";
    }

};
#endif //NOAPPLICABLEACTIONEXCEPTION_H

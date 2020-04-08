#ifndef INCOMPATIBLESTATETYPEEXCEPTION_H
#define INCOMPATIBLESTATETYPEEXCEPTION_H

#include <exception>

struct IncompatibleStateTypeException : public std::exception {

    const char* what() const noexcept override {
        return "This operations requires operands to be of the same State subclass";
    }

};

#endif //INCOMPATIBLESTATETYPEEXCEPTION_H

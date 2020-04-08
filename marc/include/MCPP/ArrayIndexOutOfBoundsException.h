#ifndef ARRAYINDEXOUTOFBOUNDSEXCEPTION_H
#define ARRAYINDEXOUTOFBOUNDSEXCEPTION_H

#include <exception>

struct ArrayIndexOutOfBoundsException : public std::exception {

    const char* what() const noexcept override {
        return "Illegal access to array position (array size exceeded)";
    }

};


#endif //ARRAYINDEXOUTOFBOUNDSEXCEPTION_H

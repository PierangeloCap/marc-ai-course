#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include <exception>

struct NullPointerException : public std::exception {

    const char* what() const noexcept override {
        return "Dangling pointer detected - accessing will result in SIGSEGV";
    }

};

#endif //NULLPOINTEREXCEPTION_H

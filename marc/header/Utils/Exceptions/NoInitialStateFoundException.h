#ifndef NOINITIALPROBLEMFOUND_H
#define NOINITIALPROBLEMFOUND_H

#include <exception>

struct NoInitialStateFoundException : public std::exception {

private:
	std::string function;

public:
	NoInitialStateFoundException(std::string function)
		: std::exception(), function(function) {}
    
    const char* what() const noexcept override {
        std::string msg = std::string("Invocation of function ") + function 
            + std::string(" requires definition of an initial state");
        return msg.c_str();
    }
    
};

#endif /* NOINITIALPROBLEMFOUND_H */


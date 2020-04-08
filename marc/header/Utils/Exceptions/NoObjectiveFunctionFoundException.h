#ifndef NOOBJECTIVEFUNCTIONFOUNDEXCEPTION_H
#define NOOBJECTIVEFUNCTIONFOUNDEXCEPTION_H

#include <exception>

struct NoObjectiveFunctionFoundException : public std::exception {

private:
	std::string function;

public:
	NoObjectiveFunctionFoundException(std::string function)
		: std::exception(), function(function) {}
    
    const char* what() const noexcept override { 
        std::string msg = std::string("Invocation of function ") + function 
            + std::string(" requires definition of an objective function");
        return msg.c_str();
    }

};

#endif //NOOBJECTIVEFUNCTIONFOUNDEXCEPTION_H

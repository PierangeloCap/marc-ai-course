#ifndef NOHEURISTICFUNCTIONFOUNDEXCEPTION_H
#define NOHEURISTICFUNCTIONFOUNDEXCEPTION_H

#include <exception>

struct NoHeuristicFunctionFoundException : public std::exception {

private:
	std::string function;

public:
	NoHeuristicFunctionFoundException(std::string function)
		: std::exception(), function(function) {}

    const char* what() const noexcept override {
        std::string msg = std::string("Invocation of function ") + function 
            + std::string(" requires definition of a heuristic function");
        return msg.c_str();
    }

};

#endif //NOHEURISTICFUNCTIONFOUNDEXCEPTION_H

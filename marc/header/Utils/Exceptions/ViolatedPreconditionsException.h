#ifndef VIOLATEDPRECONDITIONSEXCEPTION_H
#define VIOLATEDPRECONDITIONSEXCEPTION_H

#include <exception>

struct ViolatedPreconditionsException : public std::exception {

private:
	std::string function;

	std::string objectClass;

public:
	ViolatedPreconditionsException(std::string objectClass, std::string function)
	    : std::exception(), objectClass(objectClass), function(function) {}

    const char* what() const noexcept override {
    	std::string msg = std::string("Detected violation of preconditions of\nFunction: ")
    	    + function + std::string("\nIn class: ") + objectClass;
        return msg.c_str();
    }

};


#endif //VIOLATEDPRECONDITIONSEXCEPTION_H

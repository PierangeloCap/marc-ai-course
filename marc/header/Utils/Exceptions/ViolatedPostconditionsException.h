#ifndef VIOLATEDPOSTCONDITIONSEXCEPTION_H
#define VIOLATEDPOSTCONDITIONSEXCEPTION_H

#include <exception>

struct ViolatedPostconditionsException : public std::exception {

private:
	std::string function;

	std::string objectClass;

public:
	ViolatedPostconditionsException(std::string objectClass, std::string function)
	    : std::exception(), objectClass(objectClass), function(function) {}

    const char* what() const noexcept override {
    	std::string msg = std::string("Detected violation of postconditions of\nFunction: ")
    	    + function + std::string("\nIn class: ") + objectClass;
        return msg.c_str();
    }

};


#endif //VIOLATEDPOSTCONDITIONSEXCEPTION_H

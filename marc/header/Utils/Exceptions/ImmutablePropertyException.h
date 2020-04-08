#ifndef IMMUTABLEPROPERTYEXCEPTION_H
#define IMMUTABLEPROPERTYEXCEPTION_H

#include <exception>

struct ImmutablePropertyException : public std::exception {

private:
	std::string className;

	std::string property;

public:
	ImmutablePropertyException(const char* className, const char* property)
	    : std::exception(), className(className), property(property) {}

    const char* what() const noexcept override {
        std::string msg = 
            std::string("Illegal attempt to modify immutable property ") + property +
            std::string(" of class ") + className;
        return msg.c_str();
    }

};

#endif //IMMUTABLEPROPERTYEXCEPTION_H

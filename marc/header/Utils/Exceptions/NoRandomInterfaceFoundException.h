#ifndef NORANDOMINTERFACEFOUNDEXCEPTION_H
#define NORANDOMINTERFACEFOUNDEXCEPTION_H

#include <exception>

struct NoRandomInterfaceFoundException : public std::exception {
    
private:
	std::string function;

public:
	NoRandomInterfaceFoundException(std::string function)
		: std::exception(), function(function) {}
    
    const char* what() const noexcept override { 
        std::string msg = std::string("Invocation of function ") + function 
            + std::string(" requires random interface");
        return msg.c_str();
    }

};

#endif //NORANDOMINTERFACEFOUNDEXCEPTION_H


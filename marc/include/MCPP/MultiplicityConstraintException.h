#ifndef MULTIPLICITYCONSTRAINTEXCEPTION_H
#define MULTIPLICITYCONSTRAINTEXCEPTION_H

#include <exception>

struct MultiplicityConstraintException : public std::exception {

private:
	std::string roleName;

	std::string association;

	unsigned int links;

public:

	MultiplicityConstraintException(unsigned int links) : std::exception(), links(links) {
		this->roleName = "";
		this->association = "";
    }

	MultiplicityConstraintException(const char* roleName, const char* assoc, unsigned int links)
	    : std::exception(), roleName(roleName), association(assoc), links(links) {}

    const char* what() const noexcept override {
    	std::string msg;
    	if (roleName == "") 
    		msg = std::string("Multiplicity constraint violated with ") + std::to_string(links) + std::string(" links");
    	else 
    		msg = std::string("The number of ") + association + std::string(" links held by this ") + roleName 
    	    + std::string(" violate multiplicity constraints (") + std::to_string(links) + std::string(" links exist)");
    	return msg.c_str();
    }

};

#endif //MULTIPLICITYCONSTRAINTEXCEPTION_H

#ifndef NOSOLUTIONFOUNDEXCEPTION_H
#define NOSOLUTIONFOUNDEXCEPTION_H

#include <exception>

struct NoSolutionFoundException : public std::exception {
    
    const char* what() const throw() {
        return "Search procedure ended with no solution";
    }
    
};



#endif /* NOSOLUTIONFOUNDEXCEPTION_H */


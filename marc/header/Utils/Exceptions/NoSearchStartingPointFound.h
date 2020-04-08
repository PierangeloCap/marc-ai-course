#ifndef NOSEARCHSTARTINGPOINTFOUND_H
#define NOSEARCHSTARTINGPOINTFOUND_H

#include <exception>

struct NoSearchStartingPointFound : public std::exception {
    
    const char* what() const throw() {
        return "Search procedure failed: starting point (random State, initial State, best Solution) undefined";
    }
    
};

#endif // NOSEARCHSTARTINGPOINTFOUND_H 


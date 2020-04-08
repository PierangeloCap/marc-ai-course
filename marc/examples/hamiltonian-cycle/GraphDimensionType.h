#ifndef GRAPHDIMENSIONTYPE_H
#define GRAPHDIMENSIONTYPE_H

#include <map>
#include "Modeling/ProblemDimensionType.h"
#include "utils/Using.h"


class GraphDimensionType : public Modeling::ProblemDimensionType {

private:
    const Graph dim;

public:
    [[nodiscard]] const Graph getDim() const {
        return this->dim;
    }

    explicit GraphDimensionType(Graph dim) : dim(std::move(dim)) { }

};


#endif //GRAPHDIMENSIONTYPE_H

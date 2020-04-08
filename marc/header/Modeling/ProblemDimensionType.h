#ifndef PROBLEMDIMENSIONTYPE_H
#define PROBLEMDIMENSIONTYPE_H

namespace Modeling {

    class ProblemDimensionType {

    protected:
        ProblemDimensionType() = default;

    public:
        ProblemDimensionType(const ProblemDimensionType& copy) = default;

        virtual ~ProblemDimensionType() = default;

    };
    
}

#endif /* PROBLEMDIMENSIONTYPE_H */


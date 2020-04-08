#ifndef JDIMENSIONTYPE_H
#define JDIMENSIONTYPE_H

#include <Modeling/ProblemDimensionType.h>
#include "JNIWrap.h"


namespace JMARC {

    class JDimensionType : public Modeling::ProblemDimensionType {

    private:
        const jobject dim;

    public:
        [[nodiscard]] const jobject getDim() const;

        explicit JDimensionType(jobject dim);

    };

}

#endif
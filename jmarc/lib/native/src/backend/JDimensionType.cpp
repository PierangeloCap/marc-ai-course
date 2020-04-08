#include "../../header/backend/JDimensionType.h"

namespace JMARC {

    [[nodiscard]] const jobject JDimensionType::getDim() const {
        return this->dim;
    }

    JDimensionType::JDimensionType(jobject dim) : dim(std::move(dim)) { }

}
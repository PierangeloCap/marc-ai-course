#ifndef VIRTUALENABLESHAREDFROMTHIS_H
#define VIRTUALENABLESHAREDFROMTHIS_H

#include <memory>

struct virtual_enable_shared_from_this_base : std::enable_shared_from_this<virtual_enable_shared_from_this_base> {
    virtual ~virtual_enable_shared_from_this_base() = default;
};

template<typename T>
struct virtual_enable_shared_from_this : virtual virtual_enable_shared_from_this_base {
    std::shared_ptr<const T> shared_from_this() const {
        return std::dynamic_pointer_cast<const T>(virtual_enable_shared_from_this_base::shared_from_this());
    }
};


#endif //VIRTUALENABLESHAREDFROMTHIS_H

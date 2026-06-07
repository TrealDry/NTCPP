#ifndef NUCLEAR_THRONE_CPP_STATUS_HPP
#define NUCLEAR_THRONE_CPP_STATUS_HPP

#include <string>

namespace ntcpp {
    enum class en_status {
        OK, NOT_OK
    };

    struct status {
        en_status stat;
        std::string msg;
    };
}

#endif

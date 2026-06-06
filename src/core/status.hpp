#ifndef NUCLEAR_THRONE_CPP_STATUS_HPP
#define NUCLEAR_THRONE_CPP_STATUS_HPP

#include <string>

namespace ntcpp {
    enum class en_status {
        INFO, WARNING, ERROR
    };

    struct status {
        en_status stat;
        std::string msg;
    };
}

#endif

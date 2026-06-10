#include "debug_manager.hpp"

#include "input_manager.hpp"

namespace ntcpp {
    void debug_manager::update() {
        if (input_manager::get_instance().get_key_status(en_keys::DEBUG) == 1)
            m_is_active = !m_is_active;
    }
}

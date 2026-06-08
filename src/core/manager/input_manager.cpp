#include "input_manager.hpp"

namespace ntcpp {
    void input_manager::update() {
        for (auto& key_pair : m_scan_codes) {
            bool is_pressed = false;

            for (auto scancode : key_pair.second) {
                if (m_sdl_keys[scancode]) {
                    is_pressed = true;
                    break;
                }
            }

            if (is_pressed) {
                if (m_keys[key_pair.first] == 1) { m_keys[key_pair.first] = 2; }
                else { m_keys[key_pair.first] = 1; }
            } else {
                if (m_keys[key_pair.first] == 1 || m_keys[key_pair.first] == 2) { m_keys[key_pair.first] = 3; }
                else if (m_keys[key_pair.first] == 3) { m_keys[key_pair.first] = 0; }
            }
        }
    }
}

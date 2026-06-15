#include "input_manager.hpp"

#include "../window.hpp"

namespace ntcpp {
    void input_manager::update() {
        static const bool* m_sdl_keys = SDL_GetKeyboardState(nullptr);

        for (auto& key_pair : m_scan_codes) {
            bool is_pressed = false;

            for (auto scancode : key_pair.second) {
                if (scancode > SDL_SCANCODE_F19 && scancode < SDL_SCANCODE_EXECUTE) {  // mouse handle
                    is_pressed = window::get_instance().m_mouse_buttons[static_cast<en_mouse_buttons>(scancode - SDL_SCANCODE_F20)];
                } else if (m_sdl_keys[scancode]) {
                    is_pressed = true;
                    break;
                }
            }

            if (is_pressed) {
                if (m_keys[key_pair.first] == 1) { m_keys[key_pair.first] = 2; }
                else if (m_keys[key_pair.first] != 2) { m_keys[key_pair.first] = 1; }
            } else {
                if (m_keys[key_pair.first] == 1 || m_keys[key_pair.first] == 2) { m_keys[key_pair.first] = 3; }
                else if (m_keys[key_pair.first] == 3) { m_keys[key_pair.first] = 0; }
            }
        }
    }
}

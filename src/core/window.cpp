#include "window.hpp"

#include "manager/obj_manager.hpp"
#include "manager/debug_manager.hpp"
#include "manager/input_manager.hpp"
#include "manager/sound_manager.hpp"
#include "manager/texture_manager.hpp"

namespace ntcpp {
    std::optional<status> window::init(SDL_Window* win, SDL_Renderer* renderer) {
        m_window = win;
        m_renderer = renderer;

        reset_mouse_buttons();

        if (auto stat = texture_manager::get_instance().init(m_renderer)) return stat;
        if (auto stat = sound_manager::get_instance().init()) return stat;
        if (auto stat = obj_manager::get_instance().init()) return stat;

        return std::nullopt;
    }

    void window::update() {
        input_manager::get_instance().update();
        debug_manager::get_instance().update();
        obj_manager::get_instance().update();
        camera::get_instance().update();
    }

    void window::draw() {
        obj_manager::get_instance().draw(m_renderer);
    }

    void window::reset_mouse_buttons() {
        m_mouse_buttons = {
            {en_mouse_buttons::LEFT, false},
            {en_mouse_buttons::MIDDLE, false},
            {en_mouse_buttons::RIGHT, false},
            {en_mouse_buttons::WHEEL_DOWN, false},
            {en_mouse_buttons::WHEEL_UP, false}
        };
    }
}

#ifndef NUCLEAR_THRONE_CPP_CURSOR_HPP
#define NUCLEAR_THRONE_CPP_CURSOR_HPP

#include "../../../core/window.hpp"
#include "../../../core/animation.hpp"
#include "../../../core/obj_interface.hpp"

namespace ntcpp {
    class cursor : obj_interface {
    public:
        std::optional<status> init() {
            if (auto stat = m_sprite.init(
                {"sprCrosshair_0"}, 1.f, false,
                &m_mouse_pos
            )) return stat;

            if (auto sprite_data = m_sprite.get_frame_data(0)) {
                m_crosshair_size = {sprite_data.value().first.w, sprite_data.value().first.h};
                m_crosshair_size /= 2.f;
            } else {
                return status {
                    en_status::NOT_OK, "crosshair get frame problem"
                };
            }

            return std::nullopt;
        }

        void update() override {
            m_mouse_pos = window::get_instance().m_mouse_pos;
            m_mouse_pos -= m_crosshair_size;

            m_sprite.update();
        }

        void draw(SDL_Renderer* renderer) override {
            m_sprite.draw(renderer);
        }
    private:
        animation m_sprite;

        vec2 m_crosshair_size;
        vec2 m_mouse_pos;
    };
}

#endif

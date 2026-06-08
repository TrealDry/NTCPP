#include "cursor.hpp"

namespace ntcpp {
    std::optional<status> cursor::init() {
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

    void cursor::update() {
        m_mouse_pos = window::get_instance().m_mouse_pos;
        m_mouse_pos -= m_crosshair_size;

        m_sprite.update();
    }

    void cursor::draw(SDL_Renderer* renderer) {
        m_sprite.draw(renderer);
    }
}
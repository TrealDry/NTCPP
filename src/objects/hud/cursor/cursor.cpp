#include "cursor.hpp"

#include "../../../core/game.hpp"

namespace ntcpp {
    std::optional<status> cursor::init() {
        if (auto stat = m_sprite.init(
            "sprCrosshair_0", {8.f, 8.f}
        )) return stat;

        return std::nullopt;
    }

    void cursor::draw(SDL_Renderer* renderer) {
        m_sprite.draw(renderer, game::get_instance().m_mouse_pos, true);
    }
}

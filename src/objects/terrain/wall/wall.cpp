#include "wall.hpp"

#include "../../../core/manager/collision_manager.hpp"

namespace ntcpp {
    void wall::init(vec2 pos) {
        m_pos = pos;
        m_sprite.init("sprWall1Bot_0", {0.f, 0.f});

        auto hitbox_down = get_global_hitbox();
        hitbox_down.y += 16.f;

        if (!collision_manager::floor_collided(hitbox_down)) {
            m_dont_draw = true;
        }
    }

    void wall::draw(SDL_Renderer* renderer) {
        if (m_dont_draw) return;

        m_sprite.draw(renderer, m_pos);
    }
}

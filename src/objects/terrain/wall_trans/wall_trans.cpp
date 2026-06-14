#include "wall_trans.hpp"

namespace ntcpp {
    void wall_trans::init(vec2 pos) {
        m_pos = pos;
        m_sprite.init("sprWall1Trans_0", {0.f, 8.f});
    }

    void wall_trans::draw(SDL_Renderer* renderer) {
        m_sprite.draw(renderer, m_pos);
    }
}

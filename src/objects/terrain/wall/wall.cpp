#include "wall.hpp"

namespace ntcpp {
    void wall::init(vec2 pos) {
        m_pos = pos;
        m_sprite.init("sprWall1Bot_0", &m_pos, {0.f, 0.f});
    }

    void wall::update() {
        ;
    }

    void wall::draw(SDL_Renderer* renderer) {
        m_sprite.draw(renderer);
    }
}

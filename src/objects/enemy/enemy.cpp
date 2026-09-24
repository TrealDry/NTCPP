#include "enemy.hpp"

namespace ntcpp {
    void enemy::update() {
        if (!m_is_alive) return;

        m_anim.update();

        if (m_hp <= 0) {
            m_is_alive = false;
            return;
        }
    }

    void enemy::draw(SDL_Renderer* renderer) {
        m_anim.draw(renderer, m_pos);
    }
}

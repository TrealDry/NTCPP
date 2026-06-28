#include "bullet_system.hpp"

namespace ntcpp {
    void bullet_system::add_bullet(bullet& b) {
        m_bullets.push_back(b);
    }

    void bullet_system::update() {
        for (auto& b : m_bullets) b.update();
    }

    void bullet_system::draw(SDL_Renderer* renderer) {
        for (auto& b : m_bullets) b.draw(renderer);
    }
}

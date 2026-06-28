#include "bullet.hpp"

namespace ntcpp {
    void bullet::init(vec2 pos, vec2 dir, unsigned char team = 1) {
        m_pos = pos;
        m_dir = dir;
        m_team = team;

        m_anim.init(
            {"sprBullet1_0", "sprBullet1_1"},
            c_standard_anim_fps, false, {6.f, 8.f}
        );

        m_anim.play();
        m_anim.update();
    }

    void bullet::update() {
        m_pos += m_dir * m_speed;
        m_anim.update();
    }

    void bullet::draw(SDL_Renderer* renderer) {
        m_anim.draw(renderer, m_pos);
    }
}

#ifndef NUCLEAR_THRONE_CPP_BULLET_HPP
#define NUCLEAR_THRONE_CPP_BULLET_HPP

#include "../../math/vec2.hpp"
#include "../../core/animation.hpp"
#include "../../core/obj_interface.hpp"

namespace ntcpp {
    class bullet : obj_interface {
    public:
        void init(vec2 pos, vec2 dir, unsigned char team);

        void update() override;
        void draw(SDL_Renderer* renderer) override;

    private:
        animation m_anim;
        vec2 m_pos = {};
        vec2 m_dir = {};
        float m_speed = 16.f;
        unsigned char m_team = 1;  // 1 = player
    };
}

#endif

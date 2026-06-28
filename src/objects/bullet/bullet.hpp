#ifndef NUCLEAR_THRONE_CPP_BULLET_HPP
#define NUCLEAR_THRONE_CPP_BULLET_HPP

#include "../../math/vec2.hpp"
#include "../../math/circle.hpp"
#include "../../core/animation.hpp"
#include "../../core/obj_interface.hpp"

namespace ntcpp {
    class bullet : obj_interface {
    public:
        bool is_alive = true;

    public:
        void init(vec2 pos, float angle_rad, unsigned char team = 1);

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        void collided();

        circle get_global_hitbox();
        vec2 get_global_hitbox_pos();

    private:
        animation m_anim;
        vec2 m_pos = {};

        vec2 m_dir = {};
        float m_angle_rad = 0.f;

        circle m_hitbox = {};
        float m_speed = 16.f;
        unsigned char m_team = 1;  // 1 = player
    };
}

#endif

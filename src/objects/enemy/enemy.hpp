#ifndef NUCLEAR_THRONE_CPP_ENEMY_HPP
#define NUCLEAR_THRONE_CPP_ENEMY_HPP

#include "../../math/vec2.hpp"
#include "../../core/manager/animation_manager.hpp"

namespace ntcpp {
    class enemy {
    public:
        bool m_is_alive = true;

        int m_max_hp = 1;
        int m_hp = 1;

        float m_speed = 0.3f;
        float m_friction = 0.4f;
        float m_weapon_kick = 0.f;

        float m_contact_damage = 0.f;

        animation_manager m_anim;

        vec2 m_pos = {};
        SDL_FRect m_hitbox = {};

        unsigned char m_team = 2;
        unsigned int m_entity_id = 0;

        unsigned int m_rad_drop = 0;

    public:
        void init(vec2 pos);

        void update();
        void draw(SDL_Renderer* renderer);
    };
}

#endif

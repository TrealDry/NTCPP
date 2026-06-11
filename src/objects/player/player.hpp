#ifndef NUCLEAR_THRONE_CPP_PLAYER_HPP
#define NUCLEAR_THRONE_CPP_PLAYER_HPP

#include "../../core/manager/animation_manager.hpp"
#include "../../core/obj_interface.hpp"
#include "../../core/status.hpp"
#include "../../math/frect.hpp"
#include "../../math/vec2.hpp"

#include <optional>

namespace ntcpp {
    class player : public obj_interface {
    public:
        std::optional<status> init();

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        SDL_FRect get_global_hitbox() { return vec2_addiction(m_hitbox, m_position); }

        void move_and_collide(float step, bool is_y);

    private:
        SDL_FRect m_hitbox = {-4.f, -4.f, 8.f, 10.f};

        vec2 m_position = {16.f, 16.f};
        vec2 m_velocity;
        float m_speed = 3.f;
        float m_friction = 0.45f;

        animation_manager m_anim;

        bool m_on_move = false;

    private:
        inline void movement();
        inline void collided();
        inline void change_flip();
        inline void anim_change();
    };
}

#endif

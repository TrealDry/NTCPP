#ifndef NUCLEAR_THRONE_CPP_PLAYER_HPP
#define NUCLEAR_THRONE_CPP_PLAYER_HPP

#include "../../core/manager/animation_manager.hpp"
#include "../../core/obj_interface.hpp"
#include "../../math/vec2.hpp"

#include <optional>
#include "../../core/status.hpp"

namespace ntcpp {
    class player : public obj_interface {
    public:
        std::optional<status> init();

        void update() override;
        void draw(SDL_Renderer* renderer) override;

    private:
        vec2 m_position;
        vec2 m_velocity;
        float m_speed = 3.f;
        float m_friction = 0.45f;

        animation_manager m_anim;

        bool m_on_move = false;

    private:
        inline void movement();
        inline void change_flip();
        inline void anim_change();
    };
}

#endif

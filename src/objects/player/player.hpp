#ifndef NUCLEAR_THRONE_CPP_PLAYER_HPP
#define NUCLEAR_THRONE_CPP_PLAYER_HPP

#include "../../core/obj_interface.hpp"
#include "../../math/vec2.hpp"

namespace ntcpp {
    class player : public obj_interface {
    public:
        vec2 m_position;
        vec2 m_velocity;
        float m_speed = 3.f;
        float m_friction = 0.45f;

    public:
        void update() override;
        void draw(SDL_Renderer* renderer) override;
    };
}

#endif

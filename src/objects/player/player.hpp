#ifndef NUCLEAR_THRONE_CPP_PLAYER_HPP
#define NUCLEAR_THRONE_CPP_PLAYER_HPP

#include "../../core/obj_interface.hpp"
#include "../../core/animation.hpp"
#include "../../math/vec2.hpp"

namespace ntcpp {
    class player : public obj_interface {
    public:
        std::optional<status> init() {
            if (auto stat = m_idle.init(
                {"sprMutant1Idle_0", "sprMutant1Idle_1", "sprMutant1Idle_2", "sprMutant1Idle_3"},
                13.5f, true, &m_position
            )) return stat;

            m_idle.play();
            return std::nullopt;
        }

        void update() override;
        void draw(SDL_Renderer* renderer) override;

    private:
        vec2 m_position;
        vec2 m_velocity;
        float m_speed = 3.f;
        float m_friction = 0.45f;

        animation m_idle;
    };
}

#endif

#ifndef NUCLEAR_THRONE_CPP_WEAPON_HPP
#define NUCLEAR_THRONE_CPP_WEAPON_HPP

#include "../../math/vec2.hpp"
#include "../../core/animation.hpp"
#include "../../core/obj_interface.hpp"

namespace ntcpp {
    class weapon : public obj_interface {
    public:
        void init(std::initializer_list<std::string_view> sprite_names, vec2 origin, bool on_hand, float angle_deg = 0.f);

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        bool is_on_hand() { return m_on_hand; }
    private:
        vec2 m_pos = {};
        vec2 m_origin = {};
        animation m_anim = {};

        float m_angle_deg = 0.f;

        bool m_on_hand = false;
    };
}

#endif

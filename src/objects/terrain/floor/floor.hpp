#ifndef NUCLEAR_THRONE_CPP_FLOOR_HPP
#define NUCLEAR_THRONE_CPP_FLOOR_HPP

#include "../../../math/vec2.hpp"
#include "../../../math/frect.hpp"
#include "../../../core/sprite.hpp"
#include "../../../core/obj_interface.hpp"

namespace ntcpp {
    class floor : obj_interface {
    public:
        void init(vec2 pos);

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        vec2& get_pos() { return m_pos; }
        SDL_FRect& get_hitbox() { return m_hitbox; }

        SDL_FRect get_global_hitbox() { return vec2_addiction(m_hitbox, m_pos); }

        void create_walls();
    private:
        SDL_FRect m_hitbox = {0.f, 0.f, 32.f, 32.f};

        vec2 m_pos = {};
        sprite m_sprite;
    };
}

#endif

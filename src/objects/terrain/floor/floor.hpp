#ifndef NUCLEAR_THRONE_CPP_FLOOR_HPP
#define NUCLEAR_THRONE_CPP_FLOOR_HPP

#include "../../../math/vec2.hpp"
#include "../../../core/sprite.hpp"
#include "../../../core/obj_interface.hpp"

namespace ntcpp {
    class floor : obj_interface {
    public:
        void init(vec2 pos);

        void update() override;
        void draw(SDL_Renderer* renderer) override;
    private:
        SDL_FRect m_hitbox = {0.f, 0.f, 32.f, 32.f};

        vec2 m_pos = {};
        sprite m_sprite;

    private:
        void create_walls();
    };
}

#endif

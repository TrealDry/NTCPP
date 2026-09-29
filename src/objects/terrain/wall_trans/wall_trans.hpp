#ifndef NUCLEAR_THRONE_CPP_WALL_TRANS_HPP
#define NUCLEAR_THRONE_CPP_WALL_TRANS_HPP

#include "../../../math/vec2.hpp"
#include "../../../core/sprite.hpp"

#include "SDL3/SDL_render.h"

namespace ntcpp {
    class wall_trans {
    public:
        void init(vec2 pos);
        void draw(SDL_Renderer* renderer);

        vec2& get_pos() { return m_pos; }

    private:
        vec2 m_pos;
        sprite m_sprite;
    };
}

#endif

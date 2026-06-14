#ifndef NUCLEAR_THRONE_CPP_WALL_TRANS_HPP
#define NUCLEAR_THRONE_CPP_WALL_TRANS_HPP

#include "../../../math/vec2.hpp"
#include "../../../core/sprite.hpp"
#include "../../../core/manager/texture_manager.hpp"

#include "SDL3/SDL_render.h"

namespace ntcpp {
    class wall_trans {
    public:
        void init(vec2 pos);
        void draw(SDL_Renderer* renderer);

    private:
        vec2 m_pos;
        sprite m_sprite;
    };
}

#endif

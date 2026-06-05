#ifndef NUCLEAR_THRONE_CPP_OBJ_INTERFACE_HPP
#define NUCLEAR_THRONE_CPP_OBJ_INTERFACE_HPP

#include "SDL3/SDL_render.h"

namespace ntcpp {
    class obj_interface {
    public:
        virtual ~obj_interface() = default;

        virtual void update() = 0;
        virtual void draw(SDL_Renderer* renderer) = 0;
    };
}

#endif

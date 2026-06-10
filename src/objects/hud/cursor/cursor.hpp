#ifndef NUCLEAR_THRONE_CPP_CURSOR_HPP
#define NUCLEAR_THRONE_CPP_CURSOR_HPP

#include "../../../core/animation.hpp"
#include "../../../core/obj_interface.hpp"
#include "../../../core/sprite.hpp"

namespace ntcpp {
    class cursor {
    public:
        std::optional<status> init();

        void draw(SDL_Renderer* renderer);
    private:
        sprite m_sprite;
    };
}

#endif

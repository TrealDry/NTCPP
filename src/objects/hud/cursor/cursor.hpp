#ifndef NUCLEAR_THRONE_CPP_CURSOR_HPP
#define NUCLEAR_THRONE_CPP_CURSOR_HPP

#include "../../../core/window.hpp"
#include "../../../core/animation.hpp"
#include "../../../core/obj_interface.hpp"

namespace ntcpp {
    class cursor : obj_interface {
    public:
        std::optional<status> init();

        void update() override;
        void draw(SDL_Renderer* renderer) override;
    private:
        animation m_sprite;

        vec2 m_crosshair_size;
        vec2 m_mouse_pos;
    };
}

#endif

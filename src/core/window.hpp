#ifndef NUCLEAR_THRONE_CPP_WINDOW_HPP
#define NUCLEAR_THRONE_CPP_WINDOW_HPP

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "obj_manager.hpp"

namespace ntcpp {
    class window {
    public:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;

        obj_manager m_obj_manager;

    public:
        void init(SDL_Window* win, SDL_Renderer* renderer) {
            m_window = win;
            m_renderer = renderer;
        }

        void update() {
            m_obj_manager.update();
        }

        void draw() {
            m_obj_manager.draw(m_renderer);
        }
    };
}

#endif

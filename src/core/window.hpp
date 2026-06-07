#ifndef NUCLEAR_THRONE_CPP_WINDOW_HPP
#define NUCLEAR_THRONE_CPP_WINDOW_HPP

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "status.hpp"
#include "../math/vec2.hpp"

#include <optional>

namespace ntcpp {
    class window {
    public:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;

        vec2 m_mouse_pos = {};

    public:
        static window& get_instance() {
            static window instance;
            return instance;
        }

        window(window const&)         = delete;
        void operator=(window const&) = delete;

        std::optional<status> init(SDL_Window* win, SDL_Renderer* renderer);

        void update();
        void draw();

    private:
        window() {}
    };
}

#endif

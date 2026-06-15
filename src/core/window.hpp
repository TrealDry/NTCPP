#ifndef NUCLEAR_THRONE_CPP_WINDOW_HPP
#define NUCLEAR_THRONE_CPP_WINDOW_HPP

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "status.hpp"
#include "../math/vec2.hpp"

#include <optional>
#include <unordered_map>

// это лучше назвать игрой, а не окном
namespace ntcpp {
    enum class en_mouse_buttons {
        LEFT = 0, MIDDLE, RIGHT, WHEEL_UP, WHEEL_DOWN
    };

    class window {
    public:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;

        vec2 m_mouse_pos = {};
        std::unordered_map<en_mouse_buttons, bool> m_mouse_buttons = {};

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

        void reset_mouse_buttons();
    };
}

#endif

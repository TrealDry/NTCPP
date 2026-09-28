#pragma once

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "status.hpp"
#include "../math/vec2.hpp"

#include <optional>
#include <unordered_map>

#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

namespace ntcpp {
    enum class en_mouse_buttons {
        LEFT = 0, MIDDLE, RIGHT, WHEEL_UP, WHEEL_DOWN
    };

    class game {
    public:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;

        vec2 m_mouse_pos = {};
        std::unordered_map<en_mouse_buttons, bool> m_mouse_buttons = {};

        int m_current_fps = 0;

        sol::state m_lua_state;
        std::string m_path_to_assets;

    public:
        static game& get_instance() {
            static game instance;
            return instance;
        }

        game(game const&)           = delete;
        void operator=(game const&) = delete;

        std::optional<status> init(SDL_Window* win, SDL_Renderer* renderer);

        void update();
        void draw();

    private:
        game() {}

        void set_path();
        void reset_mouse_buttons();
    };
}

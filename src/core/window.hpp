#ifndef NUCLEAR_THRONE_CPP_WINDOW_HPP
#define NUCLEAR_THRONE_CPP_WINDOW_HPP

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

#include "obj_manager.hpp"
#include "texture_manager.hpp"

namespace ntcpp {
    class window {
    public:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;

        obj_manager& m_obj_manager = obj_manager::get_instance();
        texture_manager& m_texture_manager = texture_manager::get_instance();

    public:
        static window& get_instance() {
            static window instance;
            return instance;
        }

        window(window const&)         = delete;
        void operator=(window const&) = delete;

        std::optional<status> init(SDL_Window* win, SDL_Renderer* renderer) {
            m_window = win;
            m_renderer = renderer;

            auto tex_manager_result = m_texture_manager.init(m_renderer);
            if (tex_manager_result.has_value()) return tex_manager_result;

            return std::nullopt;
        }

        void update() {
            m_obj_manager.update();
        }

        void draw() {
            m_obj_manager.draw(m_renderer);
        }

    private:
        window() {}
    };
}

#endif

#ifndef NUCLEAR_THRONE_CPP_ANIMATION_HPP
#define NUCLEAR_THRONE_CPP_ANIMATION_HPP

#include "texture_manager.hpp"
#include "obj_interface.hpp"
#include "../math/vec2.hpp"

constexpr float c_game_fps = 30.f;

namespace ntcpp {
    class animation : obj_interface {
    public:
        animation() : m_tex_manager(texture_manager::get_instance()) {}

        std::optional<status> init(
            std::initializer_list<std::string_view> anim_frames,
            float fps, bool loop, vec2* target_pos
        ) {
            m_fps = fps;
            m_loop = loop;

            m_target_pos = target_pos;

            m_timer_step = fps / c_game_fps;
            m_timer_limit = fps / 10.f;

            for (const auto& str_frame : anim_frames) {
                auto sprite_data = m_tex_manager.get_sprite(std::string(str_frame));  // пизда оптимизации

                if (sprite_data.has_value()) {
                    m_frames.push_back(sprite_data.value());
                } else {
                    return status{
                        en_status::NOT_OK,
                        "frame " + std::string(str_frame) + " not found"
                    };
                }
            }

            return std::nullopt;
        }

        void update() override {
            m_timer += m_timer_step;

            if (m_timer >= m_timer_limit) {
                m_timer -= m_timer_limit;

                m_current_frame++;
                if (m_current_frame >= m_frames.size()) m_current_frame = 0;
            }
        }

        void draw(SDL_Renderer* renderer) override {
            sprite_data current_frame = m_frames[m_current_frame];

            SDL_FRect dst = SDL_FRect{
                m_target_pos->x, m_target_pos->y,
                current_frame.first.w, current_frame.first.h
            };

            auto texture = m_tex_manager.get_texture(current_frame.second);

            if (!texture.has_value()) return;

            SDL_RenderTexture(
                renderer, texture.value(),
                &current_frame.first, &dst
            );
        }

        void play() { m_is_playing = true; }
        void stop() { m_is_playing = false; }

        bool is_playing() { return m_is_playing; }

    private:
        std::vector<sprite_data> m_frames;

        float m_timer = 0.f;
        float m_timer_step = 0.f;
        float m_timer_limit = 0.f;
        float m_fps = 0.f;

        vec2* m_target_pos;

        size_t m_current_frame = 0;

        texture_manager& m_tex_manager;

        bool m_is_playing = false;
        bool m_loop = false;
    };
}

#endif

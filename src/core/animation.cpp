#include "animation.hpp"

#include "camera.hpp"
#include "../math/frect.hpp"

namespace ntcpp {
    std::optional<status> animation::init(
        std::initializer_list<std::string_view> anim_frames,
        float fps, bool loop, vec2 origin
    ) {
        m_fps = fps;
        m_loop = loop;

        m_timer_step = fps / c_game_fps;
        m_timer_limit = fps / 10.f;

        m_origin = origin;

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

    void animation::update() {
        if (!m_is_playing) return;

        m_timer += m_timer_step;

        if (m_timer >= m_timer_limit) {
            m_timer -= m_timer_limit;

            m_current_frame++;
            if (m_current_frame >= m_frames.size()) {
                if (!m_loop) {
                    m_current_frame--;
                    stop();
                } else {
                    m_current_frame = 0;
                }
            }
        }
    }

    void animation::draw(SDL_Renderer* renderer, vec2 pos) {
        sprite_data current_frame = m_frames[m_current_frame];

        SDL_FRect dst;

        vec2 pos_with_origin = camera::get_instance().world_coord_to_camera(pos - m_origin);

        if (m_h_flip) {
            dst = SDL_FRect{
                pos_with_origin.x + current_frame.first.w, pos_with_origin.y,
                -current_frame.first.w, current_frame.first.h
            };
        } else {
            dst = SDL_FRect{
                pos_with_origin.x, pos_with_origin.y,
                current_frame.first.w, current_frame.first.h
            };
        }

        auto texture = m_tex_manager.get_texture(current_frame.second);

        if (!texture.has_value()) return;

        SDL_RenderTexture(
            renderer, texture.value(),
            &current_frame.first, &dst
        );
    }
}

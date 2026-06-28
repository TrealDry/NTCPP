#include "animation.hpp"

#include "../math/frect.hpp"

namespace ntcpp {
    std::optional<status> animation::init(
        std::initializer_list<std::string_view> anim_frames,
        float fps, bool loop, vec2 origin, float angle_deg, SDL_FlipMode flip
    ) {
        m_fps = fps;
        m_loop = loop;

        m_timer_step = fps / c_game_fps;
        m_timer_limit = fps / 10.f;

        m_origin = origin;

        for (const auto& str_frame : anim_frames) {
            auto sprite_data = sprite{};

            if (!sprite_data.init(std::string(str_frame), m_origin, angle_deg, flip).has_value()) {
                m_frames.push_back(sprite_data);
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

        if (m_frames[m_current_frame].get_flip() != m_flip)
            m_frames[m_current_frame].set_flip(m_flip);
    }

    void animation::draw(SDL_Renderer* renderer, vec2 pos) {
        m_frames[m_current_frame].draw(renderer, pos, m_ignore_camera);
    }
}

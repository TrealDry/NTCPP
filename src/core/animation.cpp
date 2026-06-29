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

        for (const auto& str_frame : anim_frames) {
            auto sprite_data = sprite{};

            if (!sprite_data.init(std::string(str_frame), origin, angle_deg, flip).has_value()) {
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
    }

    void animation::draw(SDL_Renderer* renderer, vec2 pos) {
        m_frames[m_current_frame].draw(renderer, pos, m_ignore_camera);
    }

    void animation::set_flip(SDL_FlipMode flip) {
        m_flip = flip;
        std::for_each(
            m_frames.begin(), m_frames.end(),
            [flip](auto& frame){ frame.set_flip(flip); }
        );
    }

    void animation::set_angle(float angle_deg) {
        std::for_each(
            m_frames.begin(), m_frames.end(),
            [angle_deg](auto& frame){ frame.set_angle(angle_deg); }
        );
    }

    void animation::set_origin(vec2 origin) {
        std::for_each(
            m_frames.begin(), m_frames.end(),
            [origin](auto& frame){ frame.set_origin(origin); }
        );
    }
}

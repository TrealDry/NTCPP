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
        );

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        void play() { m_is_playing = true; }
        void stop() { m_is_playing = false; }

        void reset() { m_current_frame = 0; m_timer = 0.f; }

        bool is_playing() { return m_is_playing; }

        void set_h_flip(bool flip) { m_h_flip = flip; }
        bool get_h_flip() { return m_h_flip; }

        std::optional<sprite_data> get_frame_data(size_t frame) {
            if (m_frames.size() <= frame) return std::nullopt;
            return m_frames[frame];
        }

    private:
        std::vector<sprite_data> m_frames;

        float m_timer = 0.f;
        float m_timer_step = 0.f;
        float m_timer_limit = 0.f;
        float m_fps = 0.f;

        vec2* m_target_pos;

        size_t m_current_frame = 0;

        texture_manager& m_tex_manager;

        bool m_h_flip = false;

        bool m_is_playing = false;
        bool m_loop = false;
    };
}

#endif

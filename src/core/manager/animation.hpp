#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "SDL3/SDL_rect.h"

struct sprite_data {
    SDL_FRect src;
    unsigned char id;
};

struct animation_data {
    uint32_t start_frame_idx;
    uint32_t frame_count;  // включая стартовый
    float frame_duration;
    bool loop;
};

class animation_manager {
public:
    static animation_manager& get_instance() {
        static animation_manager instance;
        return instance;
    }

    animation_manager(animation_manager const&)  = delete;
    void operator=(animation_manager const&) = delete;

    void init();

    void add_clip(
        const std::vector<std::string>& frames, float frame_duration, bool loop,
        const std::string& name
    );

    // я знаю про неопределенное поведения
    uint32_t get_clip_idx(const std::string& name) { return m_clip_named_idx[name]; }
    animation_data& get_clip(uint32_t index) { return m_clips[index]; }
    sprite_data& get_frame(uint32_t index) { return m_all_frames[index]; }

private:
    std::vector<sprite_data> m_all_frames{};
    std::vector<animation_data> m_clips{};
    std::unordered_map<std::string, uint32_t> m_clip_named_idx{};

private:
    animation_manager() {}
};

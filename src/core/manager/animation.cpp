#include "animation.hpp"

#include "texture_manager.hpp"

void animation_manager::init() {
    add_clip(
        {0, 2, 1.f / 14.f, false},
        {"sprBullet1_0", "sprBullet1_1"}
    );
}

void animation_manager::add_clip(animation_data clip, std::initializer_list<std::string> frames) {
    auto& tex_manager = ntcpp::texture_manager::get_instance();

    clip.start_frame_idx = m_all_frames.size();

    for (const auto& str_frame : frames) {
        auto sprite_data = tex_manager.get_sprite(str_frame);

        if (sprite_data.has_value())
            m_all_frames.push_back({sprite_data.value().first, sprite_data.value().second});
    }

    m_clips.push_back(clip);
}

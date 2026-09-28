#include "animation.hpp"

#include "../game.hpp"
#include "texture_manager.hpp"

#include <iostream>

void animation_manager::init() {
    auto& game = ntcpp::game::get_instance();
    auto& state = game.m_lua_state;

    sol::table anim_script = state.script_file(game.m_path_to_assets + "scripts/ntcpp.animation.lua");
    sol::protected_function load_script = anim_script["load"];
    load_script();
}

void animation_manager::add_clip(
    const std::vector<std::string>& frames, float frame_duration,
    bool loop, const std::string& name
) {
    auto& tex_manager = ntcpp::texture_manager::get_instance();

    animation_data clip{
        (uint32_t)m_all_frames.size(), (uint32_t)frames.size(),
        frame_duration, loop
    };

    for (const auto& str_frame : frames) {
        auto sprite_data = tex_manager.get_sprite(str_frame);

        if (sprite_data.has_value())
            m_all_frames.push_back({sprite_data.value().first, sprite_data.value().second});
    }

    m_clips.push_back(clip);
    m_clip_named_idx[name] = m_clips.size() - 1;

    std::cout << "new anim \"" << name << "\" on index " << m_clips.size() - 1 << std::endl;
}

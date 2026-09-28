#include "lua_init_state.hpp"

#include "manager/animation.hpp"

namespace ntcpp {
    void lua_init_state(sol::state& state) {
        auto anim = state.create_table();
        anim["add"] = [](const std::string& name, const sol::table& frames_table, float duration, bool loop) {
            auto frames = frames_table.as<std::vector<std::string>>();

            animation_manager::get_instance().add_clip(frames, duration, loop, name);
        };

        state["animation"] = anim;
    }
}
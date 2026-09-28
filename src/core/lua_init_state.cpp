#include "lua_init_state.hpp"

#include "manager/animation.hpp"

namespace ntcpp {
    void lua_init_state(sol::state& state) {
        auto anim = state.create_table();

        anim["add"] = [](
            const std::string& name, const sol::table& frames_table,
            const sol::table& origin_table, float duration, bool loop
        ) {
            auto frames = frames_table.as<std::vector<std::string>>();

            animation_manager::get_instance().add_clip(
                name, frames, SDL_FPoint{origin_table[1], origin_table[2]},
                duration, loop
            );
        };

        state["animation"] = anim;
    }
}
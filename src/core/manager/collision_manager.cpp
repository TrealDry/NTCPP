#include "obj_manager.hpp"
#include "collision_manager.hpp"
#include "../../objects/terrain/wall/wall.hpp"

namespace ntcpp {
    std::optional<std::pair<wall*, SDL_FRect>> collision_manager::wall_collided(SDL_FRect hitbox) {
        for (auto& _wall : obj_manager::get_instance().m_terrain.get_walls()) {
            SDL_FRect result;
            SDL_FRect global_hitbox = _wall.get_global_hitbox();

            if (SDL_GetRectIntersectionFloat(&hitbox, &global_hitbox, &result)) {
                return std::pair{&_wall, result};
            }
        }

        return std::nullopt;
    }
}

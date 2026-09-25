#ifndef NUCLEAR_THRONE_CPP_COLLISION_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_COLLISION_MANAGER_HPP

#include <optional>

#include "SDL3/SDL_rect.h"
#include "../../math/vec2.hpp"
#include "../../math/circle.hpp"

namespace ntcpp {
    class wall;

    class collision_manager {
    public:
        collision_manager() = delete;

        static std::optional<std::pair<wall*, SDL_FRect>> wall_collided(SDL_FRect hitbox);
        static std::optional<wall*> wall_circle_collided(circle hitbox);
        static bool floor_collided(SDL_FRect hitbox);

        static bool has_wall(vec2 pos);
        static bool has_floor(vec2 pos);
        static bool has_wall_trans(vec2 pos);

        static SDL_FRect get_global_hitbox(float global_x, float global_y, SDL_FRect hitbox) {
            return {hitbox.x + global_x, hitbox.y + global_y, hitbox.w, hitbox.h};
        }

        static circle get_global_hitbox(float global_x, float global_y, circle hitbox) {
            return {hitbox.x + global_x, hitbox.y + global_y, hitbox.r};
        }
    };
}

#endif

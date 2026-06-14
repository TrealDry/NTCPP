#ifndef NUCLEAR_THRONE_CPP_COLLISION_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_COLLISION_MANAGER_HPP

#include <optional>

#include "SDL3/SDL_rect.h"

namespace ntcpp {
    class wall;

    class collision_manager {
    public:
        collision_manager() = delete;

        static std::optional<std::pair<wall*, SDL_FRect>> wall_collided(SDL_FRect hitbox);
        static bool floor_collided(SDL_FRect hitbox);

        static bool has_wall(vec2 pos);
        static bool has_floor(vec2 pos);
    };
}

#endif

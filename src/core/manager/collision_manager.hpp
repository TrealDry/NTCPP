#ifndef NUCLEAR_THRONE_CPP_COLLISION_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_COLLISION_MANAGER_HPP

#include <optional>

#include "SDL3/SDL_rect.h"

namespace ntcpp {
    class wall;

    class collision_manager {
    public:
        static collision_manager& get_instance() {
            static collision_manager instance;
            return instance;
        }

        collision_manager(collision_manager const&) = delete;
        void operator=(collision_manager const&)    = delete;

        std::optional<std::pair<wall*, SDL_FRect>> wall_collided(SDL_FRect hitbox);

    private:
        collision_manager() {}
    };
}

#endif

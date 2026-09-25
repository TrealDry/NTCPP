#ifndef NUCLEAR_THRONE_CPP_ECS_SYSTEM_HPP
#define NUCLEAR_THRONE_CPP_ECS_SYSTEM_HPP

#include "entt/entt.hpp"

class ecs_system {
    public:
        virtual ~ecs_system() = default;

        virtual void update(entt::registry& reg) = 0;
};

#endif

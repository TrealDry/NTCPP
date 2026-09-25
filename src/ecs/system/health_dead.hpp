#pragma once

#include "template/ecs_system.hpp"

#include "../component/entity.hpp"

class health_dead_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Health>();

        view.each([&reg](auto entity, Health& health) {
            if (!health.is_alive) return;

            if (health.value <= 0) health.is_alive = false;
        });
    }
};

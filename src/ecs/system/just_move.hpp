#pragma once

#include "../component/position.hpp"
#include "template/ecs_system.hpp"

#include "../component/movement.hpp"

class just_move_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Movement, Position, JustMove>();

        view.each([&](auto entity, const Movement& mov, Position& pos){
            pos.x += mov.vel_x;
            pos.y += mov.vel_y;
        });
    }
};
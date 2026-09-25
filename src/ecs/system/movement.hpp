#pragma once

#include "template/ecs_system.hpp"

#include "../component/position.hpp"
#include "../component/movement.hpp"

class movement_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Movement, WantMove, Position>();

        view.each([&reg](auto entity, Movement& mov, const WantMove& want_mov, Position& pos) {

        mov.vel_x += want_mov.normalized_x * mov.speed;
        mov.vel_y += want_mov.normalized_y * mov.speed;

        // speed limit
        float current_speed = std::hypot(mov.vel_x, mov.vel_y);
        if (current_speed > mov.max_speed) {
            float scale = mov.max_speed / current_speed;
            mov.vel_x *= scale;
            mov.vel_y *= scale;
            current_speed = mov.max_speed;
        }

        // friction
        if (current_speed > 0.f) {
            float new_speed = std::fmax(0.f, current_speed - mov.friction);
            float friction_scale = new_speed / current_speed;
            mov.vel_x *= friction_scale;
            mov.vel_y *= friction_scale;
        }

        // check move
        if (mov.vel_x == 0.f && mov.vel_y == 0.f) {
            mov.on_move = false;
        } else {
            mov.on_move = true;
        }

        if (reg.any_of<MoveAndCollideWall>(entity)) return;

        // change position
        pos.x += mov.vel_x;
        pos.y += mov.vel_y;

        });
    }
};

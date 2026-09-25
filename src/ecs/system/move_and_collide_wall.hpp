#pragma once

#include "template/ecs_system.hpp"

#include "../../core/manager/collision_manager.hpp"

#include "../component/position.hpp"
#include "../component/movement.hpp"
#include "../component/hitbox.hpp"

static SDL_FRect get_global_hitbox(const Position& pos, const RectHitbox& hitbox) {  // TODO перенести в менеджер
    return {
        hitbox.rect.x + pos.x,
        hitbox.rect.y + pos.y,
        hitbox.rect.w,
        hitbox.rect.h
    };
}

class move_and_collide_wall_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Movement, RectHitbox, Position, MoveAndCollideWall>();

        view.each([](auto entity, Movement& mov, const RectHitbox& hitbox, Position& pos) {

        for (int i = 0; i < 2; i++) {  // i = 0 is x, or = 1 is y
            float step = 0.f;

            if (i == 0) {step = mov.vel_x; pos.x += mov.vel_x;}
            else        {step = mov.vel_y; pos.y += mov.vel_y;}

            auto wall_collided = ntcpp::collision_manager::wall_collided(get_global_hitbox(pos, hitbox));

            if (wall_collided) {
                float overlapX = wall_collided.value().second.w;
                float overlapY = wall_collided.value().second.h;

                if (i == 0) {
                    pos.x -= (step > 0.f) ? overlapX : -overlapX;
                    mov.vel_x = 0;
                }
                else {
                    pos.y -= (step > 0.f) ? overlapY : -overlapY;
                    mov.vel_y = 0;
                }
            }
        }

        });
    }
};

#pragma once

#include "template/ecs_system.hpp"

#include "../component/entity.hpp"
#include "../component/hitbox.hpp"
#include "../component/visible.hpp"
#include "../component/position.hpp"
#include "../component/movement.hpp"
#include "../component/projectile.hpp"

#include "../../core/manager/collision_manager.hpp"

class projectile_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Position, Projectile, Movement, WantMove, Health, CircleHitbox>();

        view.each([&](
            auto entity, const Position& pos, const Projectile& proj,
            Movement& mov, WantMove& want_mov, Health& health, const CircleHitbox& hitbox
        ) {
            if (!health.is_alive) {
                mov.vel_x = 0.f;
                mov.vel_y = 0.f;
                want_mov.normalized_x = 0.f;
                want_mov.normalized_y = 0.f;

                return;
            }

            want_mov.normalized_x = proj.const_normalized_x;
            want_mov.normalized_y = proj.const_normalized_y;

            auto wall_collided = ntcpp::collision_manager::wall_circle_collided(
                ntcpp::collision_manager::get_global_hitbox(
                    pos.x, pos.y, hitbox.circle
                )
            );

            if (wall_collided) {
                health.is_alive = false;
                health.value = 0;

                if (reg.any_of<Sprite>(entity)) {
                    reg.get<Sprite>(entity).hide = true;
                }
            }
        });
    }
};

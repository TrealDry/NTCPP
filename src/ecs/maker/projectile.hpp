#pragma once

#include "entt/entt.hpp"

#include "../../math/vec2.hpp"
#include "../../math/circle.hpp"

#include "../component/hitbox.hpp"
#include "../component/entity.hpp"
#include "../component/visible.hpp"
#include "../component/position.hpp"
#include "../component/movement.hpp"
#include "../component/projectile.hpp"

void make_projectile(entt::registry& reg, float x, float y, float angle_deg) {
    auto entity = reg.create();

    reg.emplace<Position>(entity, x, y);
    reg.emplace<Movement>(entity, 0.f, 0.f, 16.f, 16.f, 0.f, false);
    reg.emplace<WantMove>(entity, 0.f, 0.f);
    reg.emplace<Health>(entity, 1, 1, true);
    reg.emplace<CircleHitbox>(entity, ntcpp::circle{8.f, 0.f, 1.f});
    reg.emplace<Sprite>(entity, "sprBullet1_1", SDL_FPoint{6.f, 8.f}, -1, SDL_FLIP_NONE);

    auto dir = ntcpp::vec2::normalize_angle(angle_deg);
    reg.emplace<Projectile>(entity, dir.x, dir.y, (unsigned char)1);
}

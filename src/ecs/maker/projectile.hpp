#pragma once

#include "entt/entt.hpp"

#include "../../core/manager/animation.hpp"

#include "../../math/vec2.hpp"
#include "../../math/circle.hpp"

#include "../component/hitbox.hpp"
#include "../component/entity.hpp"
#include "../component/visible.hpp"
#include "../component/position.hpp"
#include "../component/movement.hpp"
#include "../component/projectile.hpp"

void make_projectile(entt::registry& reg, float x, float y, float angle_rad) {
    auto entity = reg.create();
    auto dir = ntcpp::vec2::normalize_angle(angle_rad);

    reg.emplace<Position>(entity, x, y);
    reg.emplace<Movement>(entity, 0.f, 0.f, 16.f, 16.f, 0.f, false);
    reg.emplace<WantMove>(entity, dir.x, dir.y);
    reg.emplace<JustMove>(entity);
    reg.emplace<Health>(entity, 1, 1, true);
    reg.emplace<CircleHitbox>(entity, ntcpp::circle{0.f, 0.f, 2.f});
    reg.emplace<Projectile>(entity, (unsigned char)1);

    reg.emplace<Sprite>(entity, 0, ntcpp::vec2::rad_to_deg(angle_rad));
    reg.emplace<Animation>(
        entity, animation_manager::get_instance().get_clip_idx("bullet_1")
    );
}

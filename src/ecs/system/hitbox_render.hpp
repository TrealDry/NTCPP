#pragma once

#include "../../core/game.hpp"
#include "../../core/camera.hpp"

#include "template/ecs_system.hpp"

#include "../component/hitbox.hpp"
#include "../component/position.hpp"

class hitbox_render_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Position, CircleHitbox>();

        SDL_Renderer* renderer = ntcpp::game::get_instance().m_renderer;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);

        view.each([&](
            auto entity, const Position& pos, const CircleHitbox& hitbox
        ) {
            SDL_FRect rect {
                ntcpp::camera::get_instance().world_coord_to_camera(pos.x + hitbox.circle.x - hitbox.circle.r, false),
                ntcpp::camera::get_instance().world_coord_to_camera(pos.y + hitbox.circle.y - hitbox.circle.r, true),
                hitbox.circle.r * 2,
                hitbox.circle.r * 2,
            };

            SDL_RenderRect(renderer, &rect);
        });

        auto another_view = reg.view<Position, RectHitbox>();

        another_view.each([&](
            auto entity, const Position& pos, const RectHitbox& hitbox
        ) {
            SDL_FRect rect {
                ntcpp::camera::get_instance().world_coord_to_camera(pos.x - hitbox.rect.x, false),
                ntcpp::camera::get_instance().world_coord_to_camera(pos.y - hitbox.rect.y, true),
                hitbox.rect.w,
                hitbox.rect.h,
            };

            SDL_RenderRect(renderer, &rect);
        });

    }
};

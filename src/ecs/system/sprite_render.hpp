#pragma once

#include "../../core/camera.hpp"
#include "../../core/game.hpp"
#include "../../core/manager/texture_manager.hpp"

#include "template/ecs_system.hpp"

#include "../component/position.hpp"
#include "../component/visible.hpp"

class sprite_render_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        reg.sort<Sprite>([](const auto& lhs, const auto& rhs) {
            return lhs.z_layer < rhs.z_layer;
        });

        auto view = reg.view<Position, Sprite>();
        view.use<Sprite>();

        SDL_Renderer* render = ntcpp::game::get_instance().m_renderer;

        view.each([&](auto entity, const Position& pos, const Sprite& spr) {
            if (spr.hide) return;

            auto texture = ntcpp::texture_manager::get_instance().get_texture(spr.texture_id);
            if (!texture.has_value()) return;

            SDL_FPoint offseted_pos{
                pos.x - spr.offset.x, pos.y - spr.offset.y
            };

            SDL_FRect dst;

            if (spr.ignore_camera) {
                dst = SDL_FRect{
                    offseted_pos.x,
                    offseted_pos.y,
                    spr.texture_rect.w,
                    spr.texture_rect.h
                };
            } else {
                dst = SDL_FRect{
                    ntcpp::camera::get_instance().world_coord_to_camera(offseted_pos.x, false),
                    ntcpp::camera::get_instance().world_coord_to_camera(offseted_pos.y, true),
                    spr.texture_rect.w,
                    spr.texture_rect.h
                };
            }

            SDL_RenderTextureRotated(
                render, texture.value(), &spr.texture_rect,
                &dst, spr.rotation_deg, &spr.center, spr.flip
            );
        });
    }
};

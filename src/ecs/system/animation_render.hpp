#pragma once

#include "template/ecs_system.hpp"

#include "../../core/game.hpp"
#include "../../core/camera.hpp"
#include "../../core/manager/animation.hpp"

#include "../component/visible.hpp"
#include "../component/position.hpp"

constexpr float c_delta_time_30_fps = 1.f / 30.f;

class animation_render_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        reg.sort<Animation>([](const auto& lhs, const auto& rhs) {
            return lhs.z_layer < rhs.z_layer;
        });

        auto view = reg.view<Animation, Position>();

        auto& anim_manager = animation_manager::get_instance();
        auto* renderer = ntcpp::game::get_instance().m_renderer;

        view.each([&](auto entity, Animation& anim, const Position& pos) {

        if (anim.hide) return;  // hide is also stop update

        auto& clip = anim_manager.get_clip(anim.clip_id);

        if (!anim.stop) {  // update
            anim.timer += c_delta_time_30_fps;

            if (anim.timer >= clip.frame_duration) {
                anim.timer -= clip.frame_duration;
                anim.current_frame++;

                if (anim.current_frame >= clip.frame_count) {
                    if (clip.loop) {
                        anim.current_frame = 0;
                    } else {
                        anim.current_frame--;
                        anim.stop = true;
                    }
                }
            }
        }

        // draw
        uint32_t global_index = clip.start_frame_idx + anim.current_frame;
        const auto& sprite = anim_manager.get_frame(global_index);

        auto texture = ntcpp::texture_manager::get_instance().get_texture(sprite.id);
        if (!texture.has_value()) return;

        SDL_FPoint offseted_pos{
            pos.x - anim.origin.x, pos.y - anim.origin.y
        };

        SDL_FRect dst;

        dst = SDL_FRect{
            ntcpp::camera::get_instance().world_coord_to_camera(offseted_pos.x, false),
            ntcpp::camera::get_instance().world_coord_to_camera(offseted_pos.y, true),
            sprite.src.w,
            sprite.src.h
        };

        SDL_RenderTextureRotated(
            renderer, texture.value(), &sprite.src,
            &dst, anim.rotation_deg, &anim.origin, anim.flip
        );

        });
    }
};
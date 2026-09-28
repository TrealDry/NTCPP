#pragma once

#include "template/ecs_system.hpp"

#include "../../core/manager/animation.hpp"

#include "../component/visible.hpp"
#include "../component/position.hpp"

constexpr float c_delta_time_30_fps = 1.f / 30.f;

class animation_system : public ecs_system {
public:
    void update(entt::registry& reg) override {
        auto view = reg.view<Animation, Sprite>();
        auto& anim_manager = animation_manager::get_instance();

        view.each([&](auto entity, Animation& anim, Sprite& spr) {

        auto& clip = anim_manager.get_clip(anim.clip_id);

        if (anim.stop) return;

        anim.timer += c_delta_time_30_fps;

        if (anim.timer < clip.frame_duration) {
            if (spr.texture_id == 0 && spr.texture_rect.h == 0) goto change_spr; // if is new sprite
            else return;
        };

        anim.timer -= clip.frame_duration;
        anim.current_frame++;

        if (anim.current_frame >= clip.frame_count) {
            if (clip.loop) {
                anim.current_frame = 0;
            } else {
                anim.current_frame--;
                anim.stop = true;
                return;
            }
        }

        change_spr:

        uint32_t global_index = clip.start_frame_idx + anim.current_frame;
        const auto& sprite = anim_manager.get_frame(global_index);

        spr.texture_rect = sprite.src;
        spr.texture_id = sprite.id;
        spr.origin = clip.origin;

        });
    }
};
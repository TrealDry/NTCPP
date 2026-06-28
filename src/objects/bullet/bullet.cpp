#include "bullet.hpp"

#include "../../core/manager/collision_manager.hpp"
#include "../../core/manager/debug_manager.hpp"
#include "SDL3/SDL_oldnames.h"

namespace ntcpp {
    void bullet::init(vec2 pos, float angle_rad, unsigned char team) {
        m_pos = pos;
        m_dir = vec2::normalize_angle(angle_rad);
        m_angle_rad = angle_rad;
        m_team = team;
        m_hitbox = {8.f, 0.f, 1.f};

        m_anim.init(
            {"sprBullet1_0", "sprBullet1_1"},
            c_standard_anim_fps, false, {6.f, 8.f},
            vec2::rad_to_deg(angle_rad)
        );

        m_anim.play();
        m_anim.update();
    }

    void bullet::collided() {
        if (collision_manager::wall_circle_collided(get_global_hitbox())) is_alive = false;
    }

    vec2 bullet::get_global_hitbox_pos() {
        // матрица поворота
        float cos_a = std::cos(m_angle_rad);
        float sin_a = std::sin(m_angle_rad);

        return {
            m_pos.x + (m_hitbox.x * cos_a - m_hitbox.y * sin_a),
            m_pos.y + (m_hitbox.x * sin_a - m_hitbox.y * cos_a)
        };
    }

    circle bullet::get_global_hitbox() {
        vec2 pos = get_global_hitbox_pos();
        return {pos.x, pos.y, m_hitbox.r};
    }

    void bullet::update() {
        if (!is_alive) return;

        m_pos += m_dir * m_speed;
        collided();

        m_anim.update();
    }

    void bullet::draw(SDL_Renderer* renderer) {
        if (!is_alive) return;

        m_anim.draw(renderer, m_pos);

        if (debug_manager::get_instance().m_is_active) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderPoint(
                renderer,
                camera::get_instance().world_coord_to_camera(get_global_hitbox_pos().x, false),
                camera::get_instance().world_coord_to_camera(get_global_hitbox_pos().y, true)
            );

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderPoint(
                renderer,
                camera::get_instance().world_coord_to_camera(get_global_hitbox_pos().x + m_hitbox.r, false),
                camera::get_instance().world_coord_to_camera(get_global_hitbox_pos().y + m_hitbox.r, true)
            );
        }
    }
}

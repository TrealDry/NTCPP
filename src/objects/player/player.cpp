#include "player.hpp"
#include "SDL3/SDL_render.h"

#include "../../core/game.hpp"
#include "../../core/animation.hpp"

#include "../../core/manager/input_manager.hpp"
#include "../../core/manager/collision_manager.hpp"
#include "../../core/manager/debug_manager.hpp"
#include "../../core/manager/sound_manager.hpp"

#include <cmath>

constexpr float c_max_speed = 4.f;

namespace ntcpp {
    std::optional<status> player::init(bullet_system* _bullet_system) {
        animation idle;
        animation walk;

        if (auto stat = idle.init(
            {"sprMutant1Idle_0", "sprMutant1Idle_1", "sprMutant1Idle_2", "sprMutant1Idle_3"},
            13.5f, true, {12.f, 12.f}
        )) return stat;

        if (auto stat = walk.init(
            {
                "sprMutant1Walk_0", "sprMutant1Walk_1", "sprMutant1Walk_2",
                "sprMutant1Walk_3", "sprMutant1Walk_4", "sprMutant1Walk_5"
            },
            13.5f, true, {12.f, 12.f}
        )) return stat;

        m_anim.init({&idle, &walk}, 0);

        sound_manager::get_instance().play_audio("sndMutant1Wrld");

        m_bullet_system = _bullet_system;

        return std::nullopt;
    }

    void player::move_and_collide(float step, bool is_y) {
        if (step == 0.f) return;

        if (is_y) m_position.y += step;
        else      m_position.x += step;

        auto wall_collided = collision_manager::wall_collided(get_global_hitbox());

        if (wall_collided) {
            float overlapX = wall_collided.value().second.w;
            float overlapY = wall_collided.value().second.h;

            if (is_y) {
                m_position.y -= (step > 0.f) ? overlapY : -overlapY;
                m_velocity.y = 0;
            }
            else {
                m_position.x -= (step > 0.f) ? overlapX : -overlapX;
                m_velocity.x = 0;
            }
        }
    }

    void player::fire() {
        if (input_manager::get_instance().get_key_status(en_keys::FIRE) == 1) {
            sound_manager::get_instance().play_audio("sndPistol");

            bullet b{};
            b.init(m_position, vec2::get_angle(
                camera::get_instance().world_coord_to_camera(m_position),
                game::get_instance().m_mouse_pos
            ), 1);

            m_weapon_kick = 2.f;
            m_bullet_system->add_bullet(b);
        }
    }

    void player::movement() {
        auto& input_manager = input_manager::get_instance();

        vec2 input;
        if (input_manager.get_key_status(en_keys::UP) == 1
         || input_manager.get_key_status(en_keys::UP) == 2)    input.y -= 1.f;
        if (input_manager.get_key_status(en_keys::DOWN) == 1
         || input_manager.get_key_status(en_keys::DOWN) == 2)  input.y += 1.f;
        if (input_manager.get_key_status(en_keys::LEFT) == 1
         || input_manager.get_key_status(en_keys::LEFT) == 2)  input.x -= 1.f;
        if (input_manager.get_key_status(en_keys::RIGHT) == 1
         || input_manager.get_key_status(en_keys::RIGHT) == 2) input.x += 1.f;

        input = vec2::normalize(input);

        m_velocity.x += input.x * m_speed;
        m_velocity.y += input.y * m_speed;

        // speed limit
        float current_speed = std::hypot(m_velocity.x, m_velocity.y);
        if (current_speed > c_max_speed) {
            float scale = c_max_speed / current_speed;
            m_velocity.x *= scale;
            m_velocity.y *= scale;
            current_speed = c_max_speed;
        }

        // friction
        if (current_speed > 0.f) {
            float new_speed = std::fmax(0.f, current_speed - m_friction);
            float friction_scale = new_speed / current_speed;
            m_velocity.x *= friction_scale;
            m_velocity.y *= friction_scale;
        }

        // check move
        if (m_velocity.x == 0.f && m_velocity.y == 0.f) {
            m_on_move = false;
        } else {
            m_on_move = true;
        }

        move_and_collide(m_velocity.x, false);
        move_and_collide(m_velocity.y, true);
    }

    void player::change_flip() {
        if (game::get_instance().m_mouse_pos.x < camera::get_instance().world_coord_to_camera(m_position.x, false)) {
            m_anim.set_flip(SDL_FLIP_HORIZONTAL);
        } else {
            m_anim.set_flip(SDL_FLIP_NONE);
        }
    }

    void player::anim_change() {
        if (m_on_move && m_anim.get_current_anim_index() == 0) {
            m_anim.change_anim(1);
        }

        if (!m_on_move && m_anim.get_current_anim_index() == 1) {
            m_anim.change_anim(0);
        }
    }

    void player::wkick_dec() {
        m_weapon_kick = std::max(m_weapon_kick - 1.f, 0.f);
    }

    void player::update() {
        m_anim.update();

        movement();
        wkick_dec();
        fire();
        change_flip();
        anim_change();
    }

    void player::draw(SDL_Renderer* renderer) {
        m_anim.draw(renderer, m_position);

        if (debug_manager::get_instance().m_is_active) {
            auto global_hitbox = get_global_hitbox();
            global_hitbox = SDL_FRect{
                camera::get_instance().world_coord_to_camera(global_hitbox.x, false),
                camera::get_instance().world_coord_to_camera(global_hitbox.y, true),
                global_hitbox.w, global_hitbox.h
            };

            SDL_SetRenderDrawColor(renderer, 102, 102, 102, 200);
            SDL_RenderRect(renderer, &global_hitbox);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderPoint(
                renderer,
                camera::get_instance().world_coord_to_camera(m_position.x, false),
                camera::get_instance().world_coord_to_camera(m_position.y, true)
            );
        }
    }
}

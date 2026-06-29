#include "weapon.hpp"

#include "../../core/window.hpp"
#include "../../core/manager/obj_manager.hpp"

namespace ntcpp {
    inline float lengthdir_x(float len, float dir_rad) { return len * std::cos(dir_rad); }
    inline float lengthdir_y(float len, float dir_rad) { return len * std::sin(dir_rad); }

    void weapon::init(std::initializer_list<std::string_view> sprite_names, vec2 origin, bool on_hand, float angle_deg) {
        m_anim.init(
            sprite_names, c_standard_anim_fps, true, origin
        );

        m_origin = origin;
        m_on_hand = on_hand;
        m_angle_deg = angle_deg;
    }

    void weapon::update() {
        m_anim.update();
    }

    void weapon::draw(SDL_Renderer* renderer) {
        if (m_on_hand) {
            auto& player = obj_manager::get_instance().m_player;

            if (player.get_anim_manager().get_flip() != SDL_FLIP_NONE && m_anim.get_flip() == SDL_FLIP_NONE) {
                m_anim.set_flip(SDL_FLIP_VERTICAL);
                m_anim.set_origin({
                    m_origin.x, m_anim.get_frame_data(0).value().get_sprite_data().first.h - m_origin.y
                });
            } else if (player.get_anim_manager().get_flip() == SDL_FLIP_NONE && m_anim.get_flip() == SDL_FLIP_VERTICAL) {
                m_anim.set_flip(SDL_FLIP_NONE);
                m_anim.set_origin(m_origin);
            }

            vec2 pos_on_hand = player.get_pos();

            float aim_dir_rad = vec2::get_angle(
                camera::get_instance().world_coord_to_camera(player.get_pos()),
                window::get_instance().m_mouse_pos
            );

            float final_angle_deg = vec2::rad_to_deg(aim_dir_rad) + (m_angle_deg * (1.0f - (player.m_weapon_kick / 20.0f)));

            pos_on_hand.x += lengthdir_x(
                -player.m_weapon_kick,
                vec2::deg_to_rad(final_angle_deg)
            );

            pos_on_hand.y += lengthdir_y(
                -player.m_weapon_kick,
                vec2::deg_to_rad(final_angle_deg)
            ) + player.m_swap_move;

            m_anim.set_angle(final_angle_deg);
            m_anim.draw(renderer, pos_on_hand);
        } else {
            m_anim.draw(renderer, m_pos);
        }
    }
}

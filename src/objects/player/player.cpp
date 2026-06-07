#include "player.hpp"
#include "SDL3/SDL_render.h"

#include "../../core/window.hpp"
#include "../../core/texture_manager.hpp"

#include <cmath>

namespace ntcpp {
    std::optional<status> player::init() {
        animation idle;
        animation walk;

        if (auto stat = idle.init(
            {"sprMutant1Idle_0", "sprMutant1Idle_1", "sprMutant1Idle_2", "sprMutant1Idle_3"},
            13.5f, true, &m_position
        )) return stat;

        if (auto stat = walk.init(
            {
                "sprMutant1Walk_0", "sprMutant1Walk_1", "sprMutant1Walk_2",
                "sprMutant1Walk_3", "sprMutant1Walk_4", "sprMutant1Walk_5"
            },
            13.5f, true, &m_position
        )) return stat;

        m_anim.init({&idle, &walk}, 0);

        return std::nullopt;
    }

    void player::movement() {
        const bool* keys = SDL_GetKeyboardState(nullptr);

        vec2 input;
        if (keys[SDL_SCANCODE_W]) input.y -= 1;
        if (keys[SDL_SCANCODE_S]) input.y += 1;
        if (keys[SDL_SCANCODE_A]) input.x -= 1;
        if (keys[SDL_SCANCODE_D]) input.x += 1;

        if (input.x != 0 || input.y != 0) {  // key move
            m_velocity = vec2::normalize(input) * m_speed;
        } else {  // friction
            if (m_velocity.x != 0.f) {
                if (m_velocity.x < 0.f) {
                    m_velocity.x = std::fmin(m_velocity.x + m_friction, 0.f);
                } else {
                    m_velocity.x = std::fmax(m_velocity.x - m_friction, 0.f);
                }
            }
            if (m_velocity.y != 0.f) {
                if (m_velocity.y < 0.f) {
                    m_velocity.y = std::fmin(m_velocity.y + m_friction, 0.f);
                } else {
                    m_velocity.y = std::fmax(m_velocity.y - m_friction, 0.f);
                }
            }
        }

        // check move
        if (m_velocity.x == 0.f && m_velocity.y == 0.f) {
            m_on_move = false;
        } else {
            m_on_move = true;
        }

        // speed limit
        if (std::abs(m_velocity.x) > 3.f) m_velocity.x = 3.f * (m_velocity.x < 0.f ? -1.f : 1.f);
        if (std::abs(m_velocity.y) > 3.f) m_velocity.y = 3.f * (m_velocity.y < 0.f ? -1.f : 1.f);

        m_position += m_velocity;
    }

    void player::change_flip() {
        if (window::get_instance().m_mouse_pos.x < m_position.x) {
            m_anim.set_h_flip(true);
        } else {
            m_anim.set_h_flip(false);
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

    void player::update() {
        m_anim.update();

        movement();
        change_flip();
        anim_change();
    }

    void player::draw(SDL_Renderer* renderer) {
        m_anim.draw(renderer);
    }
}
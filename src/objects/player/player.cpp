#include "player.hpp"
#include "SDL3/SDL_render.h"

#include "../../core/texture_manager.hpp"

#include <cmath>

namespace ntcpp {
    void player::update() {
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

        // speed limit
        if (std::abs(m_velocity.x) > 3.f) m_velocity.x = 3.f * (m_velocity.x < 0.f ? -1.f : 1.f);
        if (std::abs(m_velocity.y) > 3.f) m_velocity.y = 3.f * (m_velocity.y < 0.f ? -1.f : 1.f);

        m_position += m_velocity;
    }

    void player::draw(SDL_Renderer* renderer) {
        auto& tex_manager = texture_manager::get_instance();

        auto spr_data = tex_manager.get_sprite("sprMutant1Idle_0");

        if (spr_data.has_value()) {
            auto texture = tex_manager.get_texture(spr_data.value().second);
            if (!texture.has_value()) return;

            SDL_FRect dst = SDL_FRect{m_position.x, m_position.y, 24.f, 24.f};

            SDL_RenderTexture(
                renderer, texture.value(),
                &spr_data->first, &dst);
        } else {
            SDL_FRect rect;

            rect.x = m_position.x;
            rect.y = m_position.y;
            rect.w = rect.h = 24.f;

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
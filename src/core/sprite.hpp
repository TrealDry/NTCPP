#ifndef NUCLEAR_THRONE_CPP_SPRITE_HPP
#define NUCLEAR_THRONE_CPP_SPRITE_HPP

#include "camera.hpp"
#include "../math/vec2.hpp"
#include "manager/texture_manager.hpp"

namespace ntcpp {
    class sprite {
    public:
        std::optional<status> init(
            const std::string& sprite_name, vec2 origin,
            float angle_deg = 0.f, SDL_FlipMode flip = SDL_FLIP_NONE
        ) {
            if (auto spr_data = texture_manager::get_instance().get_sprite(sprite_name))
                m_sprite_data = spr_data.value();
            else {
                return status{
                    en_status::NOT_OK,
                    "sprite " + sprite_name + " not found"
                };
            }

            m_angle_deg = angle_deg;
            m_origin = origin;
            m_flip = flip;

            return std::nullopt;
        }

        void draw(SDL_Renderer* renderer, vec2 pos, bool ignore_camera = false) {
            auto texture = texture_manager::get_instance().get_texture(m_sprite_data.second);
            if (!texture.has_value()) return;

            vec2 pos_with_origin = pos - m_origin;

            SDL_FRect dst;

            if (ignore_camera) {
                dst = SDL_FRect{
                    pos_with_origin.x,
                    pos_with_origin.y,
                    m_sprite_data.first.w,
                    m_sprite_data.first.h
                };
            } else {
                dst = SDL_FRect{
                    camera::get_instance().world_coord_to_camera(pos_with_origin.x, false),
                    camera::get_instance().world_coord_to_camera(pos_with_origin.y, true),
                    m_sprite_data.first.w,
                    m_sprite_data.first.h
                };
            }

            SDL_FPoint center;
            center.x = m_origin.x;
            center.y = m_origin.y;

            SDL_RenderTextureRotated(
                renderer, texture.value(),
                &m_sprite_data.first, &dst,
                m_angle_deg, &center, m_flip
            );
        }

        void set_flip(SDL_FlipMode flip) { m_flip = flip; }
        SDL_FlipMode get_flip() { return m_flip; }

    private:
        sprite_data m_sprite_data;
        vec2* m_pos = nullptr;
        vec2 m_origin = {};

        float m_angle_deg = 0.f;

        SDL_FlipMode m_flip = SDL_FLIP_NONE;
    };
}

#endif

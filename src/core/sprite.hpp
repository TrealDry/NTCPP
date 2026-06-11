#ifndef NUCLEAR_THRONE_CPP_SPRITE_HPP
#define NUCLEAR_THRONE_CPP_SPRITE_HPP

#include "../math/vec2.hpp"
#include "manager/texture_manager.hpp"

namespace ntcpp {
    class sprite {
    public:
        std::optional<status> init(const std::string& sprite_name, vec2 origin) {
            if (auto spr_data = texture_manager::get_instance().get_sprite(sprite_name))
                m_sprite_data = spr_data.value();
            else {
                return status{
                    en_status::NOT_OK,
                    "sprite " + sprite_name + " not found"
                };
            }
            m_origin = origin;

            return std::nullopt;
        }

        void draw(SDL_Renderer* renderer, vec2 pos) {
            auto texture = texture_manager::get_instance().get_texture(m_sprite_data.second);
            if (!texture.has_value()) return;

            auto dst = SDL_FRect{
                pos.x - m_origin.x,
                pos.y - m_origin.y,
                m_sprite_data.first.w,
                m_sprite_data.first.h
            };

            SDL_RenderTexture(
                renderer, texture.value(),
                &m_sprite_data.first, &dst
            );
        }

    private:
        sprite_data m_sprite_data;
        vec2* m_pos = nullptr;
        vec2 m_origin = {};
    };
}

#endif

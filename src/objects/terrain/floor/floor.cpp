#include "floor.hpp"

#include "../terrain.hpp"
#include "../../../core/manager/collision_manager.hpp"
#include "../../../core/manager/obj_manager.hpp"

namespace ntcpp {
    void floor::init(vec2 pos) {
        m_pos = pos;
        m_sprite.init("sprFloor1_0", {0.f, 0.f});
    }

    void floor::create_walls() {
        static const std::array<vec2, 12> arr = {
            vec2{-16.f, -16.f}, vec2{0.f, -16.f}, vec2{16.f, -16.f}, vec2{32.f, -16.f},
            vec2{-16.f, 0.f}, vec2{32.f, 0.f}, vec2{-16.f, 16.f}, vec2{32.f, 16.f},
            vec2{-16.f, 32.f}, vec2{0.f, 32.f}, vec2{16.f, 32.f}, vec2{32.f, 32.f}
        };

        for (const auto& coord : arr) {
            if (!collision_manager::floor_collided({
                m_pos.x + coord.x,
                m_pos.y + coord.y,
                16.f, 16.f
            }))
                obj_manager::get_instance().m_terrain.create_wall(m_pos + coord);
        }
    }

    void floor::create_trans() {
        static const std::array<vec2, 20> arr = {
            vec2{-32.f, -32.f}, vec2{-16.f, -32.f}, vec2{0.f, -32.f}, vec2{16.f, -32.f},
            vec2{32.f, -32.f}, vec2{48.f, -32.f}, vec2{48.f, -16.f}, vec2{48.f, 0.f},
            vec2{48.f, 16.f}, vec2{48.f, 32.f}, vec2{48.f, 48.f}, vec2{32.f, 48.f},
            vec2{16.f, 48.f}, vec2{0.f, 48.f}, vec2{-16.f, 48.f}, vec2{-32.f, 48.f},
            vec2{-32.f, 32.f}, vec2{-32.f, 16.f}, vec2{-32.f, 0.f}, vec2{-32.f, -16.f},
        };

        for (const auto& coord : arr) {
            if (collision_manager::floor_collided({
                m_pos.x + coord.x,
                m_pos.y + coord.y,
                16.f, 16.f
            })) continue;

            if (collision_manager::wall_collided({
                m_pos.x + coord.x,
                m_pos.y + coord.y,
                16.f, 16.f
            })) continue;

            obj_manager::get_instance().m_terrain.create_wall_trans(m_pos + coord);
        }
    }

    void floor::create_single_wall() {
        if (SDL_rand(5) >= 1) return;

        SDL_FRect result;
        SDL_FRect glob_hitbox = get_global_hitbox();

        // check for wall installation ban
        for (auto& rect : obj_manager::get_instance().m_terrain.get_dont_create_walls()) {
            if (SDL_GetRectIntersectionFloat(&glob_hitbox, &rect, &result)) {
                return;
            }
        }

        SDL_FRect player_glob_hitbox = obj_manager::get_instance().m_player.get_global_hitbox();
        if (SDL_GetRectIntersectionFloat(&glob_hitbox, &player_glob_hitbox, &result)) {
            return;
        }

        // TODO сделать проверку на врагов, сундуки, колбу, лежащего ассасина, и пропы

        vec2 wall_pos{};

        if (SDL_rand(1)) wall_pos.x = 0.f;
        else wall_pos.x = 16.f;

        if (SDL_rand(1)) wall_pos.y = 0.f;
        else wall_pos.y = 16.f;

        obj_manager::get_instance().m_terrain.create_wall(m_pos + wall_pos);
        obj_manager::get_instance().m_terrain.get_dont_create_walls().push_back(get_global_hitbox());
    }

    void floor::update() {
        ;
    }

    void floor::draw(SDL_Renderer* renderer) {
        m_sprite.draw(renderer, m_pos);
    }
}

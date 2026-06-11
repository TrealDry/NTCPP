#include "floor_maker.hpp"

#include "../../../core/manager/obj_manager.hpp"

namespace ntcpp {
    vec2 velocity_from_direction(direction dir) {
        switch (dir) {
        case direction::RIGHT:
            return vec2{1.f, 0.f};
        case direction::UP:
            return vec2{0.f, -1.f};
        case direction::LEFT:
            return vec2{-1.f, 0.f};
        case direction::DOWN:
            return vec2{0.f, 1.f};
        }

        return vec2{0.f, 0.f};
    }

    void floor_maker::init(size_t goal, vec2 pos) {
        m_goal = goal;
        m_pos = pos;
        m_dir = static_cast<direction>(SDL_rand(4));

        obj_manager::get_instance().m_terrain.create_floor(m_pos);
    }

    void floor_maker::update() {
        if (obj_manager::get_instance().m_terrain.get_floors().size() > m_goal) {
            if (vec2::distance({16.f, 16.f}, m_pos) > 48.f) {
                obj_manager::get_instance().m_terrain.create_floor(m_pos);  // TODO проверить есть ли другой пол
                ; // TODO создать колбу радиации
            }

            delete_me = true;
            return;
        }

        m_pos += velocity_from_direction(m_dir) * 32;

        obj_manager::get_instance().m_terrain.create_floor(m_pos);

        if (SDL_rand(2)) {
            obj_manager::get_instance().m_terrain.create_floor({m_pos.x + 32.f, m_pos.y});
            obj_manager::get_instance().m_terrain.create_floor({m_pos.x + 32.f, m_pos.y + 32.f});
            obj_manager::get_instance().m_terrain.create_floor({m_pos.x, m_pos.y + 32.f});
        }

        static const std::array<int, 14> turn_choose {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 1, -1, 2};
        int turn = turn_choose[SDL_rand(14)];

        // какой то понос
        if (turn < 0) {
            m_dir = static_cast<direction>(
                static_cast<int>(m_dir) + turn < 0 ? 4 - (static_cast<int>(m_dir) + turn) : static_cast<int>(m_dir) + turn
            );
        } else {
            m_dir = static_cast<direction>(
                static_cast<int>(m_dir) + turn > 3 ? (static_cast<int>(m_dir) + turn) - 4 : static_cast<int>(m_dir) + turn
            );
        }

        if (turn == 2) {  // 180 angle
            obj_manager::get_instance().m_terrain.create_floor(m_pos);
            // TODO создать сундук с оружием
        }

        if (SDL_rand(20 + obj_manager::get_instance().m_terrain.get_floor_makers().size()) > 20) {
            if (vec2::distance({16.f, 16.f}, m_pos) > 48.f) {
                obj_manager::get_instance().m_terrain.create_floor(m_pos);
                ; // TODO создать сундук с патронами
            }

            delete_me = true;
        }

        if (SDL_rand(9) < 1) {
            create_duplicate = true;
        }
    }

    void floor_maker::draw(SDL_Renderer* renderer) {
        ;
    }
}

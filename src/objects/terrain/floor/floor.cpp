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
            if (!collision_manager::get_instance().has_wall(m_pos + coord)) {
                obj_manager::get_instance().m_terrain.create_wall(m_pos + coord);
            }
        }
    }

    void floor::update() {
        ;
    }

    void floor::draw(SDL_Renderer* renderer) {
        m_sprite.draw(renderer, m_pos);
    }
}

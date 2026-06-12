#include "camera.hpp"

#include "manager/obj_manager.hpp"

namespace ntcpp {
    vec2 camera::world_coord_to_camera(vec2 obj_pos) {
        return vec2{
            obj_pos.x - m_pos.x,
            obj_pos.y - m_pos.y
        };
    }

    float camera::world_coord_to_camera(float coord, bool is_y) {
        if (is_y) return coord - m_pos.y;
        return coord - m_pos.x;
    }

    void camera::update() {
        m_pos = obj_manager::get_instance().m_player.get_pos();
        m_pos.x -= 320.f / 2.f;
        m_pos.y -= 240.f / 2.f;
    }
}

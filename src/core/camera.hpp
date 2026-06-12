#ifndef NUCLEAR_THRONE_CPP_CAMERA_HPP
#define NUCLEAR_THRONE_CPP_CAMERA_HPP

#include "../math/vec2.hpp"

namespace ntcpp {
    class camera {
    public:
        static camera& get_instance() {
            static camera instance;
            return instance;
        }

        camera(camera const&)         = delete;
        void operator=(camera const&) = delete;

        vec2 world_coord_to_camera(vec2 obj_pos);
        float world_coord_to_camera(float coord, bool is_y);

        void update();

    private:
        vec2 m_pos = {};

    private:
        camera() {}
    };
}

#endif
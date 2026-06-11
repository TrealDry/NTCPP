#ifndef NUCLEAR_THRONE_CPP_FLOOR_MAKER_HPP
#define NUCLEAR_THRONE_CPP_FLOOR_MAKER_HPP

#include "../../../math/vec2.hpp"
#include "../../../core/obj_interface.hpp"

namespace ntcpp {
    enum class direction {RIGHT = 0, UP, LEFT, DOWN};  // 0, 90, 180, 270 angle
    vec2 velocity_from_direction(direction dir);

    class floor_maker : obj_interface {
    public:
        bool delete_me = false;
        bool create_duplicate = false;

    public:
        void init(size_t goal, vec2 pos);

        vec2 get_pos() { return m_pos; }

        void update() override;
        void draw(SDL_Renderer* renderer) override;

    private:
        size_t m_goal = 0;
        vec2 m_pos = {};
        direction m_dir = direction::RIGHT;
    };
}

#endif

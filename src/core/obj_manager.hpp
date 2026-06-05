#ifndef NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP

#include "../objects/player/player.hpp"

namespace ntcpp {
    class obj_manager {
    public:
        player m_player;

    public:
        static obj_manager& get_instance() {
            static obj_manager instance;
            return instance;
        }

        obj_manager(obj_manager const&)    = delete;
        void operator=(obj_manager const&) = delete;

        void update() {
            m_player.update();
        }

        void draw(SDL_Renderer* renderer) {
            m_player.draw(renderer);
        }

    private:
        obj_manager() {}
    };
}

#endif

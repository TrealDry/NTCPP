#ifndef NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP

#include "../objects/player/player.hpp"

namespace ntcpp {
    class obj_manager {
    public:
        player m_player;

    public:
        void update() {
            m_player.update();
        }

        void draw(SDL_Renderer* renderer) {
            m_player.draw(renderer);
        }
    };
}

#endif

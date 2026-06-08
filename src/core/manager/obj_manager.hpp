#ifndef NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP

#include "../../objects/hud/cursor/cursor.hpp"
#include "../../objects/player/player.hpp"

namespace ntcpp {
    class obj_manager {
    public:
        player m_player;
        cursor m_cursor;

    public:
        static obj_manager& get_instance() {
            static obj_manager instance;
            return instance;
        }

        obj_manager(obj_manager const&)    = delete;
        void operator=(obj_manager const&) = delete;

        std::optional<status> init() {
            if (auto stat = m_player.init()) return stat;
            if (auto stat = m_cursor.init()) return stat;

            return std::nullopt;
        }

        void update() {
            m_player.update();
            m_cursor.update();
        }

        void draw(SDL_Renderer* renderer) {
            m_player.draw(renderer);
            m_cursor.draw(renderer);
        }

    private:
        obj_manager() {}
    };
}

#endif

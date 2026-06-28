#ifndef NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP

#include "../../objects/hud/cursor/cursor.hpp"
#include "../../objects/player/player.hpp"
#include "../../objects/terrain/terrain.hpp"
#include "../../objects/bullet/bullet_system.hpp"

namespace ntcpp {
    class obj_manager {
    public:
        player m_player;
        cursor m_cursor;
        terrain m_terrain;
        bullet_system m_bullet_system;

    public:
        static obj_manager& get_instance() {
            static obj_manager instance;
            return instance;
        }

        obj_manager(obj_manager const&)    = delete;
        void operator=(obj_manager const&) = delete;

        std::optional<status> init() {
            m_terrain.init();

            if (auto stat = m_player.init(&m_bullet_system)) return stat;
            if (auto stat = m_cursor.init()) return stat;

            return std::nullopt;
        }

        void update() {
            m_terrain.update();
            m_player.update();
            m_bullet_system.update();
        }

        void draw(SDL_Renderer* renderer) {
            m_terrain.draw(renderer);
            m_player.draw(renderer);
            m_bullet_system.draw(renderer);

            m_terrain.draw_top_layer(renderer);

            m_cursor.draw(renderer);
        }

    private:
        obj_manager() {}
    };
}

#endif

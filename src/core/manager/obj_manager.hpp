#ifndef NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_OBJ_MANAGER_HPP

#include "../../objects/hud/cursor/cursor.hpp"
#include "../../objects/player/player.hpp"
#include "../../objects/terrain/terrain.hpp"
#include "../../objects/bullet/bullet_system.hpp"
#include "../../objects/weapon/weapon_container.hpp"

namespace ntcpp {
    class obj_manager {
    public:
        player m_player;
        cursor m_cursor;
        terrain m_terrain;
        bullet_system m_bullet_system;
        weapon_container m_weapon_container;

    public:
        static obj_manager& get_instance() {
            static obj_manager instance;
            return instance;
        }

        obj_manager(obj_manager const&)    = delete;
        void operator=(obj_manager const&) = delete;

        std::optional<status> init();

        void update();
        void draw(SDL_Renderer* renderer);

    private:
        obj_manager() {}
    };
}

#endif

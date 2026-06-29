#include "obj_manager.hpp"

namespace ntcpp {
    std::optional<status> obj_manager::init() {
        m_terrain.init();
        m_weapon_container.init();

        if (auto stat = m_player.init(&m_bullet_system)) return stat;
        if (auto stat = m_cursor.init()) return stat;

        return std::nullopt;
    }

    void obj_manager::update() {
        m_terrain.update();
        m_player.update();
        m_weapon_container.update();
        m_bullet_system.update();
    }

    void obj_manager::draw(SDL_Renderer* renderer) {
        m_terrain.draw(renderer);
        m_player.draw(renderer);
        m_weapon_container.draw(renderer);
        m_bullet_system.draw(renderer);

        m_terrain.draw_top_layer(renderer);

        m_cursor.draw(renderer);
    }
}

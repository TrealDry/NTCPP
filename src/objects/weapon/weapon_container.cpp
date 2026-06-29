#include "weapon_container.hpp"

#include "../../core/window.hpp"
#include "../../core/manager/obj_manager.hpp"

namespace ntcpp {
    void weapon_container::init() {
        weapon wep;
        wep.init({"sprRevolver_0"}, {-3.f, 3.f}, true);
        add_weapon(wep);
    }

    void weapon_container::add_weapon(weapon& w) {
        m_weapons.push_back(w);
    }

    void weapon_container::update() {
        for (auto& b : m_weapons) b.update();
    }

    void weapon_container::draw(SDL_Renderer* renderer) {
        auto pos = obj_manager::get_instance().m_player.get_pos();

        for (auto& b : m_weapons) {
            if (b.is_on_hand()) {
                if (window::get_instance().m_mouse_pos.y > camera::get_instance().world_coord_to_camera(pos.y, true)) {
                    continue;
                }
            }
            b.draw(renderer);
        }
    }

    void weapon_container::draw_top_layer(SDL_Renderer* renderer) {
        auto pos = obj_manager::get_instance().m_player.get_pos();

        for (auto& b : m_weapons) {
            if (b.is_on_hand()) {
                if (window::get_instance().m_mouse_pos.y < camera::get_instance().world_coord_to_camera(pos.y, true)) {
                    continue;
                }
            }

            b.draw(renderer);
        }
    }
}
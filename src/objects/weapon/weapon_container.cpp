#include "weapon_container.hpp"

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
        for (auto& b : m_weapons) b.draw(renderer);
    }
}
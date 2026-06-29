#ifndef NUCLEAR_THRONE_CPP_WEAPON_CONTAINER_HPP
#define NUCLEAR_THRONE_CPP_WEAPON_CONTAINER_HPP

#include "weapon.hpp"
#include "../../core/obj_interface.hpp"

namespace ntcpp {
    class weapon_container : public obj_interface {
    public:
        void init();

        void add_weapon(weapon& w);
        std::vector<weapon>& get_bullets() { return m_weapons; }

        void update() override;
        void draw(SDL_Renderer* renderer) override;

    private:
        std::vector<weapon> m_weapons;
    };
}

#endif

#ifndef NUCLEAR_THRONE_CPP_BULLET_SYSTEM_HPP
#define NUCLEAR_THRONE_CPP_BULLET_SYSTEM_HPP

#include <vector>

#include "bullet.hpp"

namespace ntcpp {
    class bullet_system : obj_interface {
    public:
        void add_bullet(bullet& b);
        std::vector<bullet>& get_bullets() { return m_bullets; }

        void update() override;
        void draw(SDL_Renderer* renderer) override;

    private:
        std::vector<bullet> m_bullets;
    };
}

#endif

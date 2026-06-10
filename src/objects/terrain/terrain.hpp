#ifndef NUCLEAR_THRONE_CPP_TERRAIN_HPP
#define NUCLEAR_THRONE_CPP_TERRAIN_HPP

#include <vector>
#include "wall/wall.hpp"

namespace ntcpp {
    class terrain : obj_interface {
    public:
        void init();

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        std::vector<wall>& get_walls() { return m_walls; }

    private:
        std::vector<wall> m_walls;
    };
}

#endif

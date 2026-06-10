#include "terrain.hpp"

namespace ntcpp {
    void terrain::init() {
        m_walls.emplace_back();
        m_walls.emplace_back();
        m_walls.emplace_back();

        m_walls[0].init({64.f, 64.f});
        m_walls[1].init({64.f, 80.f});
        m_walls[2].init({48.f, 96.f});
    }

    void terrain::update() {
        ;
    }

    void terrain::draw(SDL_Renderer* renderer) {
        for (auto& _wall : m_walls) {
            _wall.draw(renderer);
        }
    }
}

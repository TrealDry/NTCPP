#include "terrain.hpp"

namespace ntcpp {
    void terrain::init() {
        m_walls.emplace_back();
        m_walls.emplace_back();
        m_walls.emplace_back();

        m_walls[0].init({64.f, 64.f});
        m_walls[1].init({64.f, 80.f});
        m_walls[2].init({48.f, 96.f});

        m_floors.emplace_back();
        m_floors[0].init({128.f, 128.f});
    }

    void terrain::create_wall(vec2 pos) {
        m_walls.emplace_back();
        m_walls.back().init(pos);
    }

    void terrain::create_floor(vec2 pos) {
        ;
    }

    void terrain::update() {
        ;
    }

    void terrain::draw(SDL_Renderer* renderer) {
        for (auto& _floor : m_floors) {
            _floor.draw(renderer);
        }

        for (auto& _wall : m_walls) {
            _wall.draw(renderer);
        }
    }
}

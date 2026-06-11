#include "terrain.hpp"

namespace ntcpp {
    void terrain::init() {
        // m_walls.emplace_back();
        // m_walls.emplace_back();
        // m_walls.emplace_back();
        //
        // m_walls[0].init({64.f, 64.f});
        // m_walls[1].init({64.f, 80.f});
        // m_walls[2].init({48.f, 96.f});
        //
        // m_floors.emplace_back();
        // m_floors[0].init({128.f, 128.f});

        create_floor_maker({0.f, 0.f});
    }

    void terrain::create_wall(vec2 pos) {
        m_walls.emplace_back();
        m_walls.back().init(pos);
    }

    void terrain::create_floor(vec2 pos) {
        m_floors.emplace_back();
        m_floors.back().init(pos);
    }

    void terrain::create_floor_maker(vec2 pos) {
        m_floor_makers.emplace_back();
        m_floor_makers.back().init(110, pos);  // TODO сменить goal позже
    }

    void terrain::update() {
        std::vector<vec2> new_floor_makers;

        // update
        for (auto& _floor_maker : m_floor_makers) {
            _floor_maker.update();

            if (_floor_maker.create_duplicate) {
                new_floor_makers.emplace_back(_floor_maker.get_pos());
                _floor_maker.create_duplicate = false;
            }
        }

        // delete
        m_floor_makers.erase(
            std::remove_if(m_floor_makers.begin(), m_floor_makers.end(), [](auto& _floor_maker) {
                return _floor_maker.delete_me;
            }), m_floor_makers.end()
        );

        // add new fm
        std::for_each(new_floor_makers.begin(), new_floor_makers.end(), [this](vec2& new_pos) {
            create_floor_maker(new_pos);
        });
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

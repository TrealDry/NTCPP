#include "terrain.hpp"

#include "../../core/manager/collision_manager.hpp"

namespace ntcpp {
    void terrain::init() {
        create_floor_maker({0.f, 0.f});
    }

    void terrain::create_wall(vec2 pos) {
        if (collision_manager::has_wall(pos)) return;

        m_walls.emplace_back();
        m_walls.back().init(pos);
    }

    void terrain::create_floor(vec2 pos) {
        if (collision_manager::has_floor(pos)) return;

        m_floors.emplace_back();
        m_floors.back().init(pos);
    }

    void terrain::create_floor_maker(vec2 pos) {
        m_floor_makers.emplace_back();
        m_floor_makers.back().init(110, pos);  // TODO сменить goal позже
    }

    void terrain::update() {
        std::vector<vec2> new_floor_makers;

        // update floor maker
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

        if (m_floor_makers.empty() && m_gen_status == en_gen_status::CREATE_FLOORS) {
            std::for_each(m_floors.begin(), m_floors.end(), [](floor& _floor) {
                _floor.create_walls();
            });

            m_gen_status = en_gen_status::DONE;
        }
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
